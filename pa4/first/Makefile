all: first
first: first.c
	gcc -Wall -Werror -lm -fsanitize=address first.c -o first
clean:
	rm -rf first
