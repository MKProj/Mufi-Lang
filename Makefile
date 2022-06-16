STDLIB =  -lm src/stdlib/stdlib.c -lm src/stdlib/math_.c -lm src/stdlib/conv.c -lm src/stdlib/os.c -lm src/stdlib/files.c
RUST = -L mufi_stdlib/target/debug -l mufi_stdlib
SRC_FILES = $(filter-out src/vm_bench.c, $(wildcard src/*.c))
debug:
	python3 utils/debug_prod.py debug
	make build
release:
	python3 utils/debug_prod.py release
	make build
build:
	cd mufi_stdlib && cargo build --release
	clang $(SRC_FILES) $(RUST) $(STDLIB) -Werror -Wall -std=c99 -o mufi
line_count:
	echo "This file contains lines for each of the C programs and their headers." > LINE_COUNT.txt
	wc -l src/*.c src/*.h src/stdlib/*.c src/stdlib/*.h >> LINE_COUNT.txt
git_add:
	# add to git
	# needs to build and have the latest line count
	make line_count
	make release
	git add -A
version:
	make build
	./mufi version > VERSION
install:
	make release
	echo "export LD_LIBRARY_PATH=mufi_stdlib/target/release" >> ~/.bashrc
	sudo mv mufi /usr/local/bin/
test_mufi:
	python3 utils/test.py

bench:
	cd src && cargo bench
	make clean

clean:
	rm src/*.o src/libmufi.so.a

