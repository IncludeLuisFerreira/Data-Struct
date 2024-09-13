# Working on improve the makefile
CC = gcc
CC_flags = -c   -Wimplicit
SRC = src/
OBJ = obj/
H = include/
APP= app/
EXE = exe/


all:
	$(CC) $(CC_flags) $(SRC)double_linked_list.c -o $(OBJ)double_linked_list.o
	$(CC) $(APP)double_linked_list.c $(OBJ)double_linked_list.o -o  $(EXE)double_linked_list.exe

	$(CC) $(CC_flags) $(SRC)circular_linked_list.c -I $(H)/circular_linked_list.h -o $(OBJ)circular_linked_list.o
	$(CC) $(APP)circular_linked_list.c $(OBJ)circular_linked_list.o -o $(EXE)circular_linked_list.exe

	$(CC) $(CC_flags) $(SRC)stack.c -I $(H)/stack.h -o $(OBJ)stack.o
	$(CC) $(APP)stack.c $(OBJ)stack.o -o $(EXE)stack.exe

	$(CC) $(CC_flags) $(SRC)queue.c -I $(H)/queue.h -o $(OBJ)queue.o
	$(CC) $(APP)queue.c $(OBJ)queue.o -o $(EXE)queue.exe
	
	$(CC) $(CC_flags) $(SRC)tree.c -I $(H)/tree.h -o $(OBJ)tree.o
	$(CC) $(APP)tree.c $(OBJ)tree.o -o $(EXE)tree.exe

	$(CC) $(CC_flags) $(SRC)PriorityQueue.c -I $(H)PriorityQueue.c -o $(OBJ)PriorityQueue.o
	$(CC) $(APP)PriorityQueue.c $(OBJ)PriorityQueue.o -o $(EXE)PriorityQueue.exe

	$(CC) $(CC_flags) $(SRC)avltree.c -I $(H)avltree.c -o $(OBJ)avltree.o
	$(CC) $(APP)avltree.c $(OBJ)avltree.o -o $(EXE)avltree.exe

	$(CC) $(CC_flags) $(SRC)hashtable.c -I $(H)hashtable.c -o $(OBJ)hashtable.o
	$(CC) $(APP)hashtable.c $(OBJ)hashtable.o -o $(EXE)hashtable.exe

	$(CC) $(CC_flags) $(SRC)dictionary.c -I $(H)dictionary.c -o $(OBJ)dictionary.o
	$(CC) $(APP)dictionary.c $(OBJ)dictionary.o -o $(EXE)dictionary.exe