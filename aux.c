#include "aux.h"
#include "ld_file.h"

#include "rbtree.h"
#include "xxhash.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>  // FILE_*
#include <stdlib.h> // free
#include <string.h> // strdup

struct file_reader {
    FILE *fstream; // owns
    char chunk[4096 / 4];
    size_t read_count;
};

struct ld_error file_reader_init(struct file_reader *this, char const *path) {
    assert(this && path);
    this->fstream = fopen(path, "rb");
    if (!this->fstream) {
        return (struct ld_error){.type = ld_ERR_CANT_ACCESS, .message = strdup(path)};
    }
    return OK;
}

void file_reader_clear(struct file_reader *this) {
    assert(this);
    fclose(this->fstream);
}

void file_reader_next_chunk(struct file_reader *this) {
    assert(this);
    this->read_count = fread(this->chunk, 1, sizeof(this->chunk), this->fstream);
}

struct ld_error compute_hash(struct ld_file *this) {
    assert(this);
    struct ld_error err        = OK;
    XXH64_state_t *const state = XXH64_createState();
    if (!state) {
        err = OOM;
        goto clean_state;
    }
    unsigned long long seed = 5;
    if (XXH64_reset(state, seed) != XXH_OK) {
        err = (struct ld_error){.type = ld_ERR_HASHING_ERROR};
        goto clean_state;
    }
    struct file_reader reader;
    err = file_reader_init(&reader, this->path);
    if (err.type != ld_ERR_OK) {
        goto clean_state;
    }
    while (true) {
        file_reader_next_chunk(&reader);
        if (ferror(reader.fstream)) {
            err = (struct ld_error){.type = ld_ERR_CANT_ACCESS, .message = strdup(this->path)};
            goto clean_reader;
        }
        if (XXH64_update(state, reader.chunk, reader.read_count) != XXH_OK) {
            err = (struct ld_error){.type = ld_ERR_HASHING_ERROR};
            goto clean_reader;
        }
        if (feof(reader.fstream)) {
            this->hash     = XXH64_digest(state);
            this->has_hash = true;
            err            = OK;
            goto clean_reader;
        }
    }
clean_reader:
    file_reader_clear(&reader);
clean_state:
    XXH64_freeState(state);
    return err;
}

struct ld_error equal_contents(struct ld_file *file1, struct ld_file *file2, bool *result) {
    assert(result);
    assert(file1->hash == file2->hash);

    struct ld_error err = OK;

    struct file_reader reader1;
    struct file_reader reader2;
    err = file_reader_init(&reader1, file1->path);
    if (err.type != ld_ERR_OK) {
        return err;
    }
    err = file_reader_init(&reader2, file2->path);
    if (err.type != ld_ERR_OK) {
        goto clean_reader1;
    }

    while (true) {
        file_reader_next_chunk(&reader1);
        file_reader_next_chunk(&reader2);
        if (ferror(reader1.fstream)) {
            err = (struct ld_error){.type = ld_ERR_CANT_ACCESS, .message = strdup(file1->path)};
            goto clean_reader2;
        }
        if (ferror(reader2.fstream)) {
            err = (struct ld_error){.type = ld_ERR_CANT_ACCESS, .message = strdup(file2->path)};
            goto clean_reader2;
        }
        assert(reader1.read_count == reader2.read_count);
        *result = memcmp(reader1.chunk, reader2.chunk, reader1.read_count) == 0;
        if (*result == false) {
            err = OK;
            goto clean_reader2;
        }
        if (feof(reader1.fstream)) {
            assert(feof(reader2.fstream));
            err = OK;
            goto clean_reader2;
        }
    }
clean_reader2:
    file_reader_clear(&reader2);
clean_reader1:
    file_reader_clear(&reader1);
    return err;
}

struct ld_error check_if_duplicates(struct ld_file *file1, struct ld_file *file2, bool *result) {
    assert(file1 && file2);
    if (!file1->has_hash) {
        compute_hash(file1);
    }
    if (!file2->has_hash) {
        compute_hash(file2);
    }
    if (file1->hash != file2->hash) {
        *result = false;
        return OK;
    }
    return equal_contents(file1, file2, result); // TODO optimize hashing with contents compare
}

struct ld_error add_to_tree(struct ld_duplicates_tree *tree, struct ld_file *file, size_t file_size) {
    assert(file);
    struct rb_node **new = &(tree->root.rb_node), *parent = NULL;

    struct ld_duplicates_tree_node *position = NULL;

    while (*new) {
        struct ld_duplicates_tree_node *container = container_of(*new, struct ld_duplicates_tree_node, node);
        parent                                    = *new;
        if (file_size > container->file_size) {
            new = &((*new)->rb_left);
        } else if (file_size < container->file_size) {
            new = &((*new)->rb_right);
        } else {
            position = container;
            break;
        }
    }

    struct ld_ranked_list_entry *entry = malloc(sizeof(struct ld_ranked_list_entry));
    if (!entry) {
        ld_file_clear(file);
        return OOM;
    }
    entry->file = *file; // takes ownership

    if (!position) {
        position = malloc(sizeof(struct ld_duplicates_tree_node));
        if (!position) {
            ld_ranked_list_entry_destroy(entry);
            return OOM;
        }
        LD_RANKED_LIST_INIT(position, file_size);
        rb_link_node(&position->node, parent, new);
        rb_insert_color(&position->node, &tree->root);
    }

    SLIST_INSERT_HEAD(position, entry, entries);
    return OK;
}

void file_list_clear(struct file_list *this) {
    while (!SLIST_EMPTY(this)) {
        struct file_list_entry *first = SLIST_FIRST(this);
        SLIST_REMOVE_HEAD(this, entries);
        free(first);
    }
}
