
#include "server.h"

//error and perror 

/*//////////////////////////////////////////////////////////////
func name: p_error
description: print an error to the stderr and exit
return val: void
params: const char* - the nsg to print
//////////////////////////////////////////////////////////////*/
void p_error(const char* msg)
{
	cerr<< msg <<endl;
	exit(1);
}
/*//////////////////////////////////////////////////////////////
func name: error
description: print an error to the std output and exit
return val: void
params: const char* - the nsg to print
//////////////////////////////////////////////////////////////*/
void error(const char* msg)
{
	cout << msg << endl;
	exit(1);
}

/*//////////////////////////////////////////////////////////////
func name: main
description: the main func, the entire program
return val: int- 0 for success and 1 for failure
params: int argc - num of args, char** argv - array of inputs (strings)
//////////////////////////////////////////////////////////////*/
int main(int argc, char **argv) {

	// check if the number of the arguments is ok 
	if (argc > 2) {
		error("Too many arguments");
	}
	unsigned short ackNum;
	int timeoutExpiredCount = 0;
	int selector;					//descriptor of the select() func	
	int packet_len;
	FILE* file;						//file (to write) descriptor
	int sock; 						//the Socket
	struct sockaddr_in ServAddr;	// local address
	struct sockaddr_in ClntAddr; 	// client address 
	WRQ WRQ_buffer; 				// buff to recv the WRQ 
	Ack ack_buffer; 				// buff to save ack 
	Packet packet_buffer; 			// buff to save data packet 
	unsigned int cliAddrLen; 		// length of client message 
	unsigned short ServPort; 		// port of the server

	//create socket for sending/receiving datagrams
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		p_error("TTFTP_ERROR: socket() failed");
	}

	//pre orders for binding (as found in google)
	memset(&ServAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServPort = (unsigned short)(atoi(argv[1]));
	ServAddr.sin_port = htons(ServPort);
	// bind to the local address 
	if (bind(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0) {
		p_error("bind() failed");
	}

	do
	{
		cliAddrLen = sizeof(ClntAddr);
		// waiting for WRQ
		int WRQ_len = recvfrom(sock, &WRQ_buffer, MAX_PACKET_SIZE, 0, (struct sockaddr *) &ClntAddr, &cliAddrLen);
		if (WRQ_len == 0) {
			error ("recvfrom () get zero bits of data");
		}
		else if (WRQ_len < 0) {
			p_error("TTFTP_ERROR: recvfrom");
		}
		// WRQ read successful:
		else {	
			WRQ_buffer.opcode = ntohs(WRQ_buffer.opcode);

			if (WRQ_buffer.opcode != 2) {
				//we assume that we keep waiting until WRQ
				printf("received not WRQ packet \n");
				continue;
			}

			// seperate WRQ buf to filename and transmission mode 
			char filename[MAX_PACKET_SIZE];				// file name
			char transmission_mode[MAX_PACKET_SIZE];	// transmission mode
			WRQ_buffer.descriptor[MAX_PACKET_SIZE - 3] = '\0';	// add string terminator 
			strcpy(filename, WRQ_buffer.descriptor);
			int filename_len = strlen(filename);
			strcpy(transmission_mode, (WRQ_buffer.descriptor + filename_len + 1));
			int transmission_mode_len = strlen(transmission_mode);
			if (transmission_mode_len != strlen("octet") || strcmp(transmission_mode, "octet") != 0) { 
			// we assume the wrong transimission mode is not a fatal error
				printf("transmission mode isnt octet\n");
				continue;
			}

			//we now have the filename and the correct transmission mode (so far so good)
			printf("IN:WRQ,%s,%s\n", filename, transmission_mode);
			file = fopen(filename, "w+");

			// 1st ack (num 0) 
			ackNum = 0;
			ack_buffer.opcode = htons(4);
			ack_buffer.blockNum = htons(ackNum);	
			int WRQ_ack_send = sendto(sock, &ack_buffer, ACK_SIZE, 0, (struct sockaddr *) &ClntAddr, sizeof(ClntAddr));
			if (WRQ_ack_send == -1) {				
				p_error("TTFTP_ERROR: sendto() failed");
			}
			else if (WRQ_ack_send != ACK_SIZE) {		 
				error("RECVFAIL");
			}
			else {
				printf("OUT:ACK,%d\n", ackNum); // print the ack for WRQ
			}
		}
		do
		{
			do
			{
				do
				{
					// TODO (Done): Wait WAIT_FOR_PACKET_TIMEOUT to see if something appears for us at the socket (we are waiting for DATA)
					struct timeval timeout;
					timeout.tv_sec = WAIT_FOR_PACKET_TIMEOUT;
					timeout.tv_usec = 0;
					fd_set readfds;
					FD_ZERO(&readfds);
					FD_CLR(sock, &readfds);
					FD_SET(sock, &readfds);

					selector = select(sock + 1, &readfds, NULL, NULL, &timeout);
					if (selector == -1) {                    // should not happen given the right socket data.
						p_error("TTFTP_ERROR: select() fail");
					}
					if (selector > 0)// TODO(Done): if there was something at the socket and we are here not because of a timeout
					{
						// TODO(Done): Read the DATA packet from the socket (at least we hope this is a DATA packet)
						packet_len = recvfrom(sock, &packet_buffer, MAX_PACKET_SIZE, 0, (struct sockaddr *) &ClntAddr, &cliAddrLen);
						if (packet_len < 0) {
							p_error("TTFTP_ERROR: error in recvfrom() ");
						}
						packet_buffer.opcode = ntohs(packet_buffer.opcode);
						packet_buffer.blockNum = ntohs(packet_buffer.blockNum);
					}
					if (selector == 0) // TODO(Done): Time out expired while waiting for data to appear at the socket
					{
						//TODO(Done): Send another ACK for the last packet
						printf("FLOWERROR: Timeout expired.\n");						                                          
						ack_buffer.blockNum = htons(ackNum);								// packet number retransmit ack
						int packet_ack_size = sendto(sock, &ack_buffer, ACK_SIZE, 0, (struct sockaddr *) &ClntAddr, sizeof(ClntAddr));
						if (packet_ack_size == -1) {								
							p_error("TTFTP_ERROR: sendto() failed");
							
						}
						else if (packet_ack_size != ACK_SIZE) {						
							error("RECVFAIL");
						}
						else {
							printf("OUT:ACK,%d\n", ackNum );											// print ack for curr packet
						}
						timeoutExpiredCount++;
					}
					if (timeoutExpiredCount >= NUMBER_OF_FAILURES)
					{
						// FATAL ERROR BAIL OUT
						error ("FLOWERROR: the limit of sending tries has reached. transmission aborted");
					}
				} while (selector == 0 || (selector > 0 && packet_len < 0)); // TODO(Done): Continue while some socket was ready but recvfrom somehow failed to read the data
				if (packet_buffer.opcode != 3) // TODO(Done): We got something else but DATA
				{
					// FATAL ERROR BAIL OUT
					error("RECVFAIL");
				}
				if (packet_buffer.blockNum != (ackNum + 1)) // TODO(Done): The incoming block number is not what we have expected, i.e. this is a DATA pkt but the block number in DATA was wrong (not last ACK’s block number + 1)
				{
					// FATAL ERROR BAIL OUT
					error ("FLOWERROR: Incorrect block number");	
				}
			} while (false);
			timeoutExpiredCount = 0;

			ackNum++;	// update the received block number
			// print out the received details
			printf("IN:DATA, %d,%d\n", ackNum, packet_len);
			// write data to file
			size_t size = 1;
			size_t nmemb = (unsigned int)(packet_len - 4);
			unsigned int file_len = fwrite((void*)packet_buffer.data, size, nmemb, file); // write next block to the file.
			if (file_len < (unsigned int)(packet_len - 4)) {		
				p_error("TTFTP_ERROR: fwrite() error");
			}
			printf("WRITING: %d\n", file_len);		
			
			// TODO(Done): send ACK packet to the client
			ack_buffer.blockNum = htons(ackNum);	// packet number to ack
			int packet_ack_size = sendto(sock, &ack_buffer, ACK_SIZE, 0, (struct sockaddr *) &ClntAddr, sizeof(ClntAddr));
			if (packet_ack_size == -1) {								
				p_error("TTFTP_ERROR: sendto() fail");
			}
			else if (packet_ack_size != ACK_SIZE) {						
				error("RECVFAIL");
			}
			else {
				printf("OUT:ACK,%d\n", ackNum);	// print the ack for packet
			}
		} while (packet_len == MAX_PACKET_SIZE); // not the end of the transmission yet

		// Successful end of transmission 
		if (fclose(file) != 0) {
			p_error("RECVFAIL");
		}
		printf("RECVOK\n");

	} while (true);// wait for new WRQ 
	return 0;
}


