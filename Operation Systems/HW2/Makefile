# Makefile for the smash program
CC = g++
CFLAGS = -g -Wall 
CCLINK = $(CC)
OBJS = main.o acc.o atm.o
RM = rm -f
# Creating the  executable
Bank: $(OBJS)
	$(CCLINK) -pthread -o Bank $(OBJS)
# Creating the object files
acc.o: acc.cpp acc.h
atm.o: atm.cpp atm.h acc.cpp acc.h
main.o: main.cpp atm.cpp atm.h acc.cpp acc.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

