BUILD = build
LDUPES_OBJECTS = $(addprefix $(BUILD)/,ldupes.o ld_context.o ld_duplicates_tree.o aux.o)

$(info $(shell mkdir -p $(BUILD)))

.PHONY: clean run

$(BUILD)/ldupes-run: ldupes-run.c $(BUILD)/libldupes.a $(BUILD)/libsize-to-str.so
	cc -O2 -o $@ $< -L $(BUILD) -l ldupes -l size-to-str -l vendor -l dl -Wl,-rpath,$(BUILD)

$(BUILD)/libldupes.a: $(BUILD)/libvendor.so $(LDUPES_OBJECTS)
	ar rcs $@ $(LDUPES_OBJECTS)

$(BUILD)/libsize-to-str.so: size_to_str.c
	cc -shared -fPIC -O2 -o $@ $^

$(BUILD)/libvendor.so: xxhash.c rbtree.c
	cc -shared -fPIC -O2 -o $@ $^

clean:
	$(RM) -r $(BUILD)

run: $(BUILD)/ldupes-run
	LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:$(BUILD)" $(BUILD)/ldupes-run $(SEARCH_AT)

$(BUILD)/%.o: %.c
	cc -c -O2 -o $@ $<
