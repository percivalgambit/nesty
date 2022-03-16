.PHONY: clean
clean:
	$(RM) -r obj/ $(CLEAN_ITEMS)

.PHONY: test
test:

.PHONY: export_compile_commands
export_compile_commands: export build_type := debug
export_compile_commands:
	$(MAKE) all
	sed -e '1s/^/[\n/' -e '$$s/,$$/\n]/' $$(find obj/debug -type f -name "*.o.json") > compile_commands.json