/**********************************************************************************
** Program name: chatclientEC.c
** Class name: CS372
** Author: Ben Fridkis
** Date: 7/19/2018
** Description: Simple client-side chat program to demonstrate socket programming.
**				**INCORPORATES EXTRA CREDIT FUNCTIONALITY - See README.TXT**
***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "getch.h"

#include "get_in_addr.h"
#include "getServerName.h"
#include "getServerPort.h"
#include "getClientHandle.h"

#define MAXPACKETSIZE 502		//Designates 500 character max. (Last 2 bytes needed for '\n' and '\0'. 
								//--See notes for getServerName, getServerPort, and getClientHandle)
#define MAXCLIENTHANDLESIZE 13	//10 characters, plus '>', ' ', and '\0'

typedef struct addrinfo addrinfo;

//typedef int bool;
//enum { false, true };

int main(int argc, char *argv[])
{
	char repeat = 'Y';
	char serverName[258], serverPort[7], clientHandle[MAXCLIENTHANDLESIZE];
	do
	{
		if(repeat != 'r' && repeat != 'R')
		{
			//Load serverName
			getServerName(serverName, argv[1]);
			//Load serverPort
			getServerPort(serverPort, argv[1], argv[2]);
			//Load clientHandle
			getClientHandle(clientHandle, argv[1], argv[2], argv[3]);
		}
		
		/*Data declarations for connection establishment & management*/
		
		//sockfd is the socket handle, which is returned from the call to socket (See Line 104).
		//numbytes is variable to hold the number of bytes/packet received from the server.
		//--numbytes is intialized to 5 due to check for incoming message of "\quit". (See Line 140.)
		int sockfd, numbytes = 5;
		
		//buffer holds the data received from the server (including the server handle).
		char buffer[MAXCLIENTHANDLESIZE] = "";				//Needs to receive max size of server handle initially,
															//--and will then receive one character at a time.
		
		//addrinfo is a STL api struct to hold server address configuration		
		addrinfo hints, *servInfo, *p;											
		
		//rv is the return value for the getaddrinfo STL function that populates
		//--the above mentioned addrinfo structs. A value other than 0 indicates
		//--an error.
		int rv;																	
		
		//destinationHostAddress holds the address of the server. 
		//--INET_ADDRSTRLEN is a library-provided constant designating 
		//--the length of an IPv4 address.
		char destinationHostAddress[INET_ADDRSTRLEN];								
		
		//clears memory of hints (addrinfo struct)
		memset(&hints, 0, sizeof(hints));
		
		//ai_family (addrinfo struct member) designates IP version.
		//--Here it is set to AF_INET to designate IPv4.
		hints.ai_family = AF_INET;
		
		//ai_socktype (addrinfo struct member) designates transport layer protocol.
		//--Here it is set to SCOK_STREAM to designate TCP.
		hints.ai_socktype = SOCK_STREAM;
		
		/*End: Data declarations for connection establishment & management*/
		
		//The following if block uses getaddrinfo as follows: 
		//--hints is passed in prepopulated with info as designated above, and servInfo
		//--is populated by the function in response. Specifically, servInfo will
		//--point to a linked list of struct addrinfos which each containing a struct
		//--sockaddr to be used to establish connection following the call to addrinfo. 
		//--The first of these sockaddr to provide viable connection parameters
		//--will be used for the connection. 
		//--The server name and server port are also designated as the first 
		//--two parameters to the function. If an error occurs, it is handled 
		//--in the following for block, and if no viable connections are provided
		//--[in the linked list pointed to by servinfo], the if following prints
		//--an error accordingly and exits execution.
		//--See reference: https://beej.us/guide/bgnet/html/multi/syscalls.html
		if((rv = getaddrinfo(serverName, serverPort, &hints, &servInfo) != 0))
		{
			printf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			return 1;
		}
		
		for(p = servInfo; p != NULL; p = p->ai_next) 
		{
			//Set up socket
			if ((sockfd = socket(p->ai_family, p->ai_socktype,
					p->ai_protocol)) == -1) 
			{
				perror("client: socket");
				continue;
			}
			//Connect to socket
			if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
			{
				close(sockfd);
				perror("client: connect");
				continue;
			}

			break;
		}
		
		if (p == NULL) 
		{
		   printf(stderr, "client: failed to connect\n");
		   return 2;
		}
		
		//Converts IP address of server to a string and prints
		inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
				destinationHostAddress, sizeof(destinationHostAddress));
		printf("\nClient: connecting to %s\n", destinationHostAddress);
		
		freeaddrinfo(servInfo); // all done with this structure
		
		printf("\n**Connected to %s**\n\n", destinationHostAddress);
		
		char quitCheck[6] = "\0", bufferDeplete[1024] = "\0";
		bool connectionEndedByClient = true;
		//While user input and server message do not equal "\quit", alternate
		//--sending and receving packets, displaying characters as they are typed on either side
		//--during that side's "active" state (i.e. during a given side's "turn to send").
		while(strcmp(quitCheck, "\\quit") != 0 && !(buffer[numbytes - 1] == 't' &&
													buffer[numbytes - 2] == 'i' &&
													buffer[numbytes - 3] == 'u' &&
													buffer[numbytes - 4] == 'q' &&
													buffer[numbytes - 5] == '\\'))
		{
			//*************************SEND******************************
			printf("\n");
			printf(clientHandle);
			int len = strlen(clientHandle);
			//Send client handle to server
			int bytes_sent = send(sockfd, clientHandle, len, 0);
			//Initialize string to hold outgoing character and set overall character count to 0
			char ch[2] = "i";
			int charCount = 0;
			while(ch[0] != '\n' && charCount < 501)
			{
				ch[0] = getch();
				
				//Update quitCheck for first 5 characters entered
				if(charCount < 5)
				{
					quitCheck[charCount] = ch[0];
				}
				
				//Echo character to screen as long as it is not a backspace with the cursor
				//--in the starting position. Increment charCount unless a backspace is echoed,
				//--in which case decrement charCount.
				if(ch[0] != 127)
				{
					printf("%c", ch[0]);
					charCount++;
				}
				else if(charCount > 0)
				{
					printf("%c", ch[0]);
					charCount--;
				}
				
				//Send character
				int bytes_sent = send(sockfd, ch, 1, 0);
			}
			putchar('\n');
			if(charCount == 501)
			{
				putchar('\n');
			}
			//END SEND
			
			//*************************RECEIVE******************************
			quitCheck[5] = '\0';
			charCount = 0;
			if (strcmp(quitCheck, "\\quit") != 0)
			{
				//Receive and print server handle
				numbytes = recv(sockfd, buffer, MAXCLIENTHANDLESIZE, 0);
				buffer[numbytes] = '\0';
				printf("%s", buffer);
				//Flush output buffer (as it won't display without either '\n' in output stream otherwise). 
				//--See https://stackoverflow.com/questions/1716296/why-does-printf-not-flush-after-the-call-unless-a-newline-is-in-the-format-strin/1716621#1716621
				fflush(stdout);
				
				buffer[0] = '\0';
				while(buffer[0] != '\r' && charCount < 501)
				{
					//Receive character from server, print to screen unless
					//--character is a backspace and cursor is at starting position
					numbytes = recv(sockfd, buffer, 1, 0);
					buffer[numbytes] = '\0';
					if((int)buffer[0] == 127 && charCount > 0)
					{
						putchar(buffer[0]);
						fflush(stdout);
						charCount--;
					}
					else
					{
						putchar(buffer[0]);
						fflush(stdout);
						charCount++;
						if(charCount < 6)
						{
							quitCheck[charCount - 1] = buffer[0];
						}
					}
				}
				putchar('\n');
				quitCheck[5] = '\0';
				if(strcmp(quitCheck, "\\quit") == 0)
				{
					connectionEndedByClient = false;
				}
				//If error, handle and exit
				if(numbytes == -1)
				{
					perror("recv");
					exit(1);
				}
			}
		}
		buffer[numbytes] = '\0';
		close(sockfd);
		if(strcmp(quitCheck, "\\quit") == 0 && connectionEndedByClient == true)
		{
			printf("\nConnection Ended By Client.\n\nReconnect or New Connection?"); 
			printf("\n-Enter 'r' for Reconnect, 'n' for New Connection, or 'q' for Quit. ");
		}
		else
		{
			printf("\n\nConnection Ended By Server.\n\nReconnect or New Connection?"); 
			printf("\n-Enter 'r' for Reconnect, 'n' for New Connection, or 'q' for Quit. ");
		}
		
		repeat = getchar();
		while(getchar() != '\n'){};		//Clear buffer after response to new connection prompt
		
		//If a new connection is desired, clear serverName, serverPort, and clientHandle
		if(repeat == 'N' || repeat == 'n')
		{
			argv[1] = NULL; argv[2] = NULL; argv[3] = NULL;
			serverName[0] = '\0'; serverPort[0] = '\0'; clientHandle[0] = '\0';
		}
	} while(repeat == 'R' || repeat == 'r' || repeat == 'N' || repeat == 'n');
	
	printf("\n\nGoodbye.\n\n");
	
	return 0;
	
}

/************************************************************************************************************************************************
   References 
** https://beej.us/guide/bgnet/html/multi/syscalls.html
** https://beej.us/guide/bgnet/html/multi/clientserver.html#simpleclient
** https://www.tutorialspoint.com/cprogramming/c_input_output.htm 
** https://stackoverflow.com/questions/8004237/how-do-i-properly-compare-strings
** https://stackoverflow.com/questions/308695/how-do-i-concatenate-const-literal-strings-in-c
** http://www.cplusplus.com/reference/cstdio/scanf/
** https://stackoverflow.com/questions/2700646/dereferencing-pointer-to-incomplete-type
** https://stackoverflow.com/questions/12024703/why-cant-getaddrinfo-be-found-when-compiling-with-gcc-and-std-c99
** https://stackoverflow.com/questions/17665793/directly-assigning-values-to-c-pointers
** https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
** https://stackoverflow.com/questions/8792317/why-cant-i-find-conio-h-on-linux
** https://stackoverflow.com/questions/1716296/why-does-printf-not-flush-after-the-call-unless-a-newline-is-in-the-format-strin/1716621#1716621
**************************************************************************************************************************************************/
