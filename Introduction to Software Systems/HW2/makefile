#This is the MAkefile for the Airport project
CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS = 
OBJS = main.o airport.o runway.o flight.o
RM = rm -f

#Creating the executable (Airport)
airport: $(OBJS)
	$(CCLINK) -o airport $(OBJS) $(LIBS)
        
#Creating object files
airport.o: airport.c airport.h runway.h ex2.h flight.h
flight.o: flight.c flight.h ex2.h
main.o: main.c airport.h runway.h ex2.h flight.h
runway.o: runway.c runway.h ex2.h flight.h

#Cleaning old files before new make
clean:
	$(RM) airport *.o *.bak *~ "H"* core
        
