##********************************************************************************
## Program name: receivingEC.py
## Class name: CS372
## Author: Ben Fridkis
## Date: 7/16/2018
## Description: Loop definition for receiving messages to remote host for chat
## 				program (to demonstrate socket programming - Program 1).
##				**INCORPORATES EXTRA CREDIT FUNCTIONALITY - See README.TXT**
##*********************************************************************************

import sys

def receive(connectionSocket, serverPort, serverHandle):	
	#Receive and print the client handle
	message = connectionSocket.recv(13).decode()
	print(message, end="")
	#Flush the output buffer (Needed for printing without newline. See https://stackoverflow.com/questions/493386/how-to-print-without-newline-or-space)
	sys.stdout.flush()
	
	chMessage = "i"
	quitCheck = ""
	charCount = 0
	while(chMessage != '\n' and charCount < 501):
		chMessage = connectionSocket.recv(1).decode()
		#Print character as long as it is not a backspace with the cursor in the starting position
		#--ord function converts to ASCII representation
		if ord(chMessage) != 127:
			print(chMessage, end="")
			charCount += 1
			#Update quitCheck variable for first 5 characters received
			if charCount < 6:
				quitCheck += chMessage
		elif charCount > 0:
			print(chMessage, end="")
			charCount -= 1
			#Update quitCheck variable for first 5 characters received
			if charCount < 6:
				quitCheck = quitCheck[:-1]
		#Flush output buffer. (See note on line 19.)
		sys.stdout.flush()
	if chMessage != "\n":
		sys.stdout.write("\n")
		
	if quitCheck != "\quit":
		return True
	#Quit if sender sends '\quit'
	else:
		connectionSocket.close()
		print("\nConnection Ended By Client.\n")
		return False