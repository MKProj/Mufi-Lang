debug:
	python3 debug_prod.py debug
	clang src/*.c -Werror -Wall -std=c99 -o mufi
release:
	python3 debug_prod.py release
	clang src/*.c -Werror -Wall -std=c99 -o mufi
line_count: 
	echo "This file contains lines for each of the C programs and their headers." > LINE_COUNT.txt
	wc -l src/*.c src/*.h >> LINE_COUNT.txt 
git_add: 
	# add to git 
	# needs to build and have the latest line count 
	make line_count 
	make release
	git add -A
version: 
	make build 
	./mufi version > VERSION
