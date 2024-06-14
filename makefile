# Working on improve the makefile

all:
	gcc -c src/double_linked_list.c -o obj/double_linked_list.o
	gcc app/double_linked_list.c obj/double_linked_list.o -o  app/double_linked_list.exe
	gcc -c src/circular_linked_list.c -I include/circular_linked_list.h -o obj/circular_linked_list.o
	gcc app/circular_linked_list.c obj/circular_linked_list.o -o app/circular_linked_list.exe
