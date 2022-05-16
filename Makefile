STDLIB =  -lm src/stdlib/stdlib.c -lm src/stdlib/math_.c -lm src/stdlib/conv.c -lm src/stdlib/os.c -lm src/stdlib/files.c -lm src/stdlib/string.c
debug:
	python3 debug_prod.py debug
	make build
release:
	python3 debug_prod.py release
	make build
build:
	clang src/*.c $(STDLIB) -Werror -Wall -std=c99 -o mufi
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