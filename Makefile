build:
	clang src/*.c -Werror -Wall -std=c99 -o mufi
install_linux:
	make build
	sudo mv mufi /usr/bin/
	echo "Finished installation, try running $ mufi to see "