#!/usr/bin/sh

gcc -ansi -pedantic -Wall -Wextra src/*.c -o kanban.debug -O0 -g && valgrind --leak-check=yes ./kanban.debug