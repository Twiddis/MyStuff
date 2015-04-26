# Macros ========================================

CC=g++
CFLAGS=-O2 -Wall -Werror -Wextra -ansi -pedantic -Wconversion -c
DIR=gnu/
OBJECTS=$(DIR)main.o $(DIR)encode.o $(DIR)decode.o
EXE=Base64.exe

# Targets ========================================

$(DIR)$(EXE) : $(OBJECTS)
	$(CC) -o $(DIR)$(EXE) $(OBJECTS)

$(DIR)main.o : main.cpp
	$(CC) -o $(DIR)main.o $(CFLAGS) main.cpp

$(DIR)encode.o : encode.cpp
	$(CC) -o $(DIR)encode.o $(CFLAGS) encode.cpp

$(DIR)decode.o : decode.cpp
	$(CC) -o $(DIR)decode.o $(CFLAGS) decode.cpp

clean :
	rm $(DIR)$(EXE) $(OBJECTS)
