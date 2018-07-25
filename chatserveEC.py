##********************************************************************************
## Program name: chatserve.py
## Class name: CS372
## Author: Ben Fridkis
## Date: 7/16/2018
## Description: Simple server-side chat program to demonstrate socket programming.
##				**INCORPORATES EXTRA CREDIT FUNCTIONALITY - See README.TXT**
## Dependencies: sendingEC.py & receivingEC.py
##*********************************************************************************

import sys
from socket import *
from receivingEC import receive
from sendingEC import send

while True:
	#Get server port number from command line argvument 1 if provided.
	#Otherwise, prompt user for server port number. (Server port number must be between 3000 and 65535.)
	try:
		serverPort
	except:	
		try:
			sys.argv[1]
			serverPort = int(sys.argv[1])
			if not (serverPort >= 3000 and serverPort <= 65535):
				print("\nCommand-line Server Port Number Specification Invalid.")
			while not (int(serverPort) >= 3000 and int(serverPort) <= 65535):
				print("Server Port Number must be an integer in range of 3000 to 65,535.\n")
				serverPort = int(input("Enter Server Port Number\n--> "))
		except Exception:			
			serverPort = int(input("\nEnter Server Port Number\n--> "))
			while not int(serverPort) >= 3000 and int(serverPort) <= 65535:
				print("Server Port Number must be an integer in range of 3000 to 65,535.")
				serverPort = int(input("Enter Server Port Number\n--> "))

	#Get server handle from command line arugment 2 if provided.
	#Otherwise, prompt user for server handle. (Use default 'Host A' if entry after prompt is blank.)	
	try:
		serverHandle
	except:
		try:
			serverHandle = sys.argv[2][:10]
		except:	
			serverHandle = input("\nEnter Server Handle. (Ten character max.)\n--> ")[:10]		
			if serverHandle == "":																
				serverHandle = "HostA"															
				print("\nHandle entry was blank. Using default handle 'HostA'.\n")
		
	#Create TCP Socket	
	serverSocket = socket(AF_INET, SOCK_STREAM)
	#Bind the port number to the socket
	socketUnbound = True
	while(socketUnbound):
		try:
			serverSocket.bind(('', serverPort))
			socketUnbound = False
		except:
			print("\nPort " + str(serverPort) + " unavailable. Select a different port.")
			serverPort = int(input("\nEnter Server Port Number\n--> "))
			while not int(serverPort) >= 3000 and int(serverPort) <= 65535:
				print("Server Port Number must be an integer in range of 3000 to 65,535.")
				serverPort = int(input("Enter Server Port Number\n--> "))
	#Listen on the Socket (max number of queued connections is 1).
	serverSocket.listen(1)
	print("\nServer Listening on Port: " + str(serverPort) + "\n")
	#Create a new socket for connection once sender initiates contact
	connectionSocket, addr = serverSocket.accept()
	print("**Connected to " 
		+ str(connectionSocket.getpeername()[0][:16]) + "**\n\n")
	connectionOpen = True
	while(connectionOpen):
		connectionOpen = receive(connectionSocket, serverPort, serverHandle)
		if connectionOpen:
			connectionOpen = send(connectionSocket, serverPort, serverHandle)

	
	
##REFERENCES##	
#https://stackoverflow.com/questions/4187185/how-can-i-check-if-my-python-object-is-a-number
#https://stackoverflow.com/questions/3474382/how-do-i-run-two-python-loops-concurrently
#https://docs.python.org/3/library/threading.html
#https://stackoverflow.com/questions/17761697/python-sys-is-not-defined
#https://www.cyberciti.biz/faq/how-do-i-find-out-what-ports-are-listeningopen-on-my-linuxfreebsd-server/
#https://unix.stackexchange.com/questions/73767/how-to-check-whether-firewall-opened-for-a-port-but-not-listening-on-the-port
#https://superuser.com/questions/602049/how-to-use-netstat-on-a-specific-port-in-linux
#https://stackoverflow.com/questions/986006/how-do-i-pass-a-variable-by-reference
#https://www.cyberciti.biz/faq/unix-linux-check-if-port-is-in-use-command/
#https://stackoverflow.com/questions/730764/how-to-properly-ignore-exceptions
#https://stackoverflow.com/questions/493386/how-to-print-without-newline-or-space