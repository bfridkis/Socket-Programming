/**********************************************************************************
** Program name: getclientHandle.c
** Class name: CS372
** Author: Ben Fridkis
** Date: 7/19/2018
** Description: Gets client handle based on command line input or, if no command line
**				input is specified, via user prompt. (Client handle needs to be
**				specified as cl_arg3.)
***********************************************************************************/

#include "getClientHandle.h"
#include "bufferClear.h"

#define MAXCLIENTHANDLESIZE 13	//10 characters, plus '>', ' ', and '\0'

void getClientHandle(char* clientHandle, char* cl_arg1, char* cl_arg2, char* cl_arg3)
{
	//clientHandle can be specified on command line when launching program, or is prompted if no
	//--command line specification is provided at launch.
	//clientHandle has a max character count of 10. An addtional two bytes are reserved for '\n' and '\0'.
	//--('\n' needed when fgets is used to determine clientHandle. See below.)
	
	//When fgets is used (i.e. when clientHandle is not determined directly from command line):
	//--An extra byte is needed in the destination character array because fgets brings in the 
	//--newline as long as the max input (specified in parameter 2 of fgets) is not reached . This is used
	//--here for input validation in the sense that a last character that is not an '\n' after  
	//--data entry indicates the user's input exceeded the input character maximum, and is thus handled accordingly. 
	//--However, because clientHandle has additional bytes reserved for the '<' and ' ' characters, which
	//--are appended after the input is received from the user, an additional byte is not explicity needed for '\n'
	//--beyond those already allocated for the maximum desired character input plus these additional characters.
	
	//clientHandle is a string with a maximum of 10 characters (entered by user).
	//--A "> " will then be appended.
	//--Ex: User enters "BenFrid", clientHandle will be "BenFrid> "
	char bufferDeplete[1024] = "\0";			
	if(cl_arg1 != NULL && cl_arg2 != NULL && cl_arg3 != NULL)
	{
		char* clientHandleTemp = (char*)malloc(sizeof(char) * 1024);
		strcpy(clientHandleTemp, cl_arg3);
		if(strlen(clientHandleTemp) > 10)
		{
			do
			{		
				printf("\nEnter client handle. (Max 10 characters)\n--> ");
				fgets(clientHandle, MAXCLIENTHANDLESIZE - 2, stdin);		//Subtracting 2 from MAXCLIENTHANDLESIZE for ' ' and '>'
				bufferClear(clientHandle, bufferDeplete);					//--'\n' of fgets replaced directly by '>' below
			} while(clientHandleTemp[strlen(clientHandleTemp) - 1] != '\n');
			clientHandle[strlen(clientHandle) - 1] = '>';
			strcat(clientHandle, " ");
		}
		else
		{
			strcpy(clientHandle, clientHandleTemp);
			strcat(clientHandle, "> ");
		}
		free(clientHandleTemp);
	}
	else
	{
		do
		{		
			printf("\nEnter client handle. (Max 10 characters)\n--> ");
			fgets(clientHandle, MAXCLIENTHANDLESIZE - 2, stdin);		//Subtracting 2 from MAXCLIENTHANDLESIZE for ' ' and '\0', while '\n'
			bufferClear(clientHandle, bufferDeplete);					//--from input is converted directly to '<' below (line 87)
		} while(clientHandle[strlen(clientHandle) - 1] != '\n');
		clientHandle[strlen(clientHandle) - 1] = '>';
		strcat(clientHandle, " ");
	}

	if(strcmp(clientHandle, "> ") == 0)
	{
		printf("\nNo handle entered. Using default of 'HostB'.\n");
		strcpy(clientHandle, "HostB> ");
	}
}