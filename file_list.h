#pragma once

struct file_list {
    struct file_list_node {
        char const *file_path;
        struct file_list_node *next;
    } * node;
};

void file_list_add(struct file_list *file_list, char const *file_path);
