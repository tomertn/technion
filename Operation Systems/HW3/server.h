#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <iostream>

using namespace std;	

#define MAX_PACKET_SIZE 516 

// parameters of the system
const int WAIT_FOR_PACKET_TIMEOUT = 3;
const int NUMBER_OF_FAILURES = 7;
const int ACK_SIZE = 4;



//structs of all types of msgs in the program:
//each struct got the exact members as written in the PDF of the HW

typedef struct WRQ_ {
	unsigned short opcode;
	char descriptor[MAX_PACKET_SIZE - 2];
}__attribute__((packed)) WRQ;

typedef struct Ack_ {
	unsigned short opcode;
	unsigned short blockNum;
}__attribute__((packed)) Ack;

typedef struct Packet_ {
	unsigned short opcode;
	unsigned short blockNum;
	char data[MAX_PACKET_SIZE - 4];
}__attribute__((packed)) Packet;

