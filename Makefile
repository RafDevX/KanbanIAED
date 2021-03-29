# horrible makefile but it works

kanban: src/*
	gcc -ansi -pedantic -Wall -Wextra src/*.c -o kanban