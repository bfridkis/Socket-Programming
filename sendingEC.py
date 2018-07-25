##********************************************************************************
## Program name: sendingEC.py
## Class name: CS372
## Author: Ben Fridkis
## Date: 7/16/2018
## Description: Loop definition for sending messages to remote host for chat
## 				program (to demonstrate socket programming - Program 1).
##				**INCORPORATES EXTRA CREDIT FUNCTIONALITY - See README.TXT**
## Dependencies: getch.py
##*********************************************************************************

import sys
from getch import getch

def send(connectionSocket, serverPort, serverHandle):
	print("\r")
	#Prompt user for message to send
	print(serverHandle + "> ", end="")
	sys.stdout.flush()
	#Send serverHandle
	connectionSocket.send((serverHandle + "> ").encode())
	
	charCount = 0
	quitCheck = ""
	outgoingCh = ''
	while(outgoingCh != '\r' and charCount < 501):
		outgoingCh = getch()
		if ord(outgoingCh) != 127:
			#Send character
			connectionSocket.send((outgoingCh).encode())
			#Echo character to screen
			print(outgoingCh, end="")
			charCount += 1
			#Update quitCheck
			if charCount < 6:
				quitCheck += outgoingCh
		elif charCount > 0:
			#Send character
			connectionSocket.send(outgoingCh.encode())
			#Echo character to screen
			print(outgoingCh, end="")
			charCount -= 1
			#Update quitCheck
			if charCount < 6:
				quitCheck = quitCheck[:-1]
		sys.stdout.flush()
		sys.stdin.flush()
	print("\n")
	
	#If message sent is '\quit', exit
	if quitCheck == "\quit":
		connectionSocket.close()
		print("\nConnection Ended By Server.\n")
		return False
	else:
		return True