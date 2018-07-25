##********************************************************************************
## Program name: sending.py
## Class name: CS372
## Author: Ben Fridkis
## Date: 7/16/2018
## Description: Loop definition for sending messages to remote host for chat
## 				program (to demonstrate socket programming - Program 1).
##*********************************************************************************

def send(connectionSocket, serverPort, serverHandle):
	print("\r")
	#Prompt user for message to send
	outgoingMessage = input(serverHandle + "> ")
	#Encode and send message with handle prepended
	connectionSocket.send((serverHandle + "> " + outgoingMessage[:500]).encode())
	#If message sent is '\quit', exit
	if outgoingMessage == "\quit":
		connectionSocket.close()
		print("\nConnection Ended By Server.\n")
		return False
	else:
		return True