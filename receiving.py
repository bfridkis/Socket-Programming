##********************************************************************************
## Program name: receiving.py
## Class name: CS372
## Author: Ben Fridkis
## Date: 7/16/2018
## Description: Loop definition for receiving messages to remote host for chat
## 				program (to demonstrate socket programming - Program 1).
##*********************************************************************************

def receive(connectionSocket, serverPort, serverHandle):	
	print("\n**Connected: Waiting for response from " 
		+ str(connectionSocket.getpeername()[0][:16]) + "**")
	message = connectionSocket.recv(512).decode()
	#Quit if sender sends '\quit'
	if message[-5:] == "\quit":
		connectionSocket.close()
		print("\nConnection Ended By Client.\n")
		return False
	#Else print received message
	else:
		print("\n" + message)
		return True