# Working on improve the makefile

all:
	gcc -c src/double_linked_list.c -o obj/double_linked_list.o
	gcc app/double_linked_list.c obj/double_linked_list.o -o  app/double_linked_list.exe