STDLIB =  -lm src/stdlib/stdlib.c
RUST = -lmufi_stdlib -L mufi_stdlib/target/debug
SRC_FILES = $(filter-out src/vm_bench.c, $(wildcard src/*.c))
debug:
	python3 utils/debug_prod.py debug
	make build
release:
	python3 utils/debug_prod.py release
	make build
build:
	cd mufi_stdlib && cargo build
	clang  $(SRC_FILES)  $(STDLIB) $(RUST) -Werror -Wall -std=c99 -o mufi
seg_debug:
	cd mufi_stdlib && cargo build
	gcc $(SRC_FILES) $(RUST) $(STDLIB) -Werror -g -Wall -std=c99 -o mufi
line_count:
	echo "This file contains lines for each of the C programs and their headers." > LINE_COUNT.txt
	wc -l src/*.c src/*.h src/stdlib/*.c mufi_stdlib/src/lib.rs src/src/*.rs src/benches/*.rs utils/*.py >> LINE_COUNT.txt
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
	sudo cp mufi_stdlib/target/debug/libmufi_stdlib.so /usr/local/lib
	echo "export LD_LIBRARY_PATH=/usr/local/lib" >> ~/.bashrc
	sudo mv mufi /usr/local/bin/
test_mufi:
	python3 utils/test.py

bench:
	cd src && cargo bench
	make clean

clean:
	rm src/*.o src/libmufi.so.a src/stdlib/*.o


