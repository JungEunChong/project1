CC = gcc
TARGETS = main
OBJECTS = main.c books.o
.SUFFIXES = .c .o
main_debug : $(TARGETS)
main_debug : DEBUGOPTION = -DDEBUG

$(TARGETS) : $(OBJECTS)
	$(CC) $(DEBUGOPTION) -o $@ $^

books.o : books.c books.h
	$(CC) $(DEBUGOPTION) -c books.c -o books.o

clean : 
	rm *.o main
