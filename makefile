# Working on improve the makefile
CC = gcc
CC_flags = -c   -Wimplicit
SRC = src/
OBJ = obj/
APP= app/
EXE = exe/


all:
	$(CC) $(CC_flags) $(SRC)double_linked_list.c -o $(OBJ)double_linked_list.o
	$(CC) $(APP)double_linked_list.c $(OBJ)double_linked_list.o -o  $(EXE)double_linked_list.exe
	$(CC) $(CC_flags) $(SRC)circular_linked_list.c -I include/circular_linked_list.h -o $(OBJ)circular_linked_list.o
	$(CC) $(APP)circular_linked_list.c $(OBJ)circular_linked_list.o -o $(EXE)circular_linked_list.exe
	$(CC) $(CC_flags) $(SRC)stack.c -I include/stack.h -o $(OBJ)stack.o
	$(CC) $(APP)stack.c $(OBJ)stack.o -o $(EXE)stack.exe
