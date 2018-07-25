/**********************************************************************************
** Program name: getServerName.c
** Class name: CS372
** Author: Ben Fridkis
** Date: 7/19/2018
** Description: Gets server name based on command line input or, if no command line
**				input is specified, via user prompt. (Server name needs to be
**				specified as argv[1].)
***********************************************************************************/

#include "getServerName.h"
#include "bufferClear.h"

void getServerName(char* serverName, char* cl_arg1)
{
	//serverName can be specified on command line when launching program, or is prompted if no
	//--command line specification is provided at launch.
	//serverName has a max character count of 256. An addtional two bytes are reserved for '\n' and '\0'.
	//--('\n' needed when fgets is used to determine serverName. See below.)
	
	//When fgets is used (i.e. when serverName is not determined directly from command line):
	//--An extra byte is needed in the destination character array because fgets brings in the 
	//--newline as long as the max input (specified in parameter 2 of fgets) is not reached . This is used
	//--here for input validation in the sense that a last character that is not an '\n' after  
	//--data entry indicates the user's input exceeded the input character maximum, and is thus handled accordingly. 
	
	char bufferDeplete[1024] = "\0";
	if(cl_arg1 != NULL)
	{
		char* serverNameTemp = (char*)malloc(sizeof(char)*1024);
		
		strcpy(serverNameTemp, cl_arg1);
		if(strlen(serverNameTemp) > 256)
		{
			do
			{		
				printf("\nEnter server name. (Max 256 characters).\n--> ");
				fgets(serverNameTemp, 258, stdin);
				bufferClear(serverNameTemp, bufferDeplete);					//--from input is converted directly to '<' below (line 87)
			} while(serverNameTemp[strlen(serverNameTemp) - 1] != '\n');
			//Remove trailing '\n'
			serverNameTemp[strlen(serverNameTemp) - 1] = '\0';
			strcpy(serverName, serverNameTemp);
		}
		else
		{
			strcpy(serverName, serverNameTemp);
		}
		free(serverNameTemp);
	}
	else
	{
		printf("\nEnter server name. (Max 256 characters.)\n--> ");
		fgets(serverName, 258, stdin);
		while(serverName[strlen(serverName) - 1] != '\n')
		{
			bufferClear(serverName, bufferDeplete);
			printf("\nEnter server name. (Max 256 characters.)\n--> ");
		}
		//Remove trailing '\n'. (See note above.)
		serverName[strlen(serverName) - 1] = '\0';
	}
}