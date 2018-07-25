README.TXT - CS372 PROGRAMMING ASSIGNMENT 1 (PROJECT 1)
AUTHOR: BENJAMIN FRIDKIS

STEPS TO EXECUTE CHATSERVE AND CHATCLIENT - A SIMPLE CHAT PROGRAM TO DEMONSTRATE SOCKET PROGRAMMING

1.  Copy the zip file "Project1_CS372_BFRIDKIS.zip" to a directory of your choice on any of the 
	  following machines:
		- flip1.engr.oregonstate.edu
		- flip2.engr.oregonstate.edu
		- flip3.engr.oregonstate.edu
		
	Unzip the contents.

2.  Type the command: "make all" (without quotes)
		- Note this generates all files for both the base program and extra credit program.
		  The base program alone can be compiled by simply typing "make" (without quotes)

3. 	Launch the python3-based server (chatserve.py), specifying a port number between 3000 and 65535
	  on the command line with program launch.
		~EX. To launch using port 35000, type: "python3 chatserve.py 35000" (without quotes)
	
	You can optionally declare the server handle as a fourth command line argument.
		~EX. To launch using port 35000 and server handle bfrid, 
			 type: "python3 chatserve.py 35000 bfrid" (without quotes)
				- Server handle must be 10 characters or less
		
	If you do not declare a server handle at the command line with program launch, you will be
	  prompted to do so at program start up. (It is also optional to declare the port number
	  in the command line with program launch. If the port number is not specified in the 
	  command line, it will also be prompted for at program start up, and in this case the 
	  server handle can not be specified on the command prompt either.)
	
	If you have selected an available port, you should see "Server Listening on Port: XXXXX",
	  where "XXXXX" is your specified port. (Note your port may also have only 4 digits, as 
	  in "XXXX".) Otherwise, you will be notified that the port selected is unavailable and 
	  asked to enter another port number. This will repeat until an available port is selected, 
	  after which the above message will display.
	
	Once "Server Listening on Port: XXXXX" displays as described above, the server is ready.

**                                     NOTE 1                                           **
**  For the following step (step 4), chatclient can be executed on the same machine     **
**  (e.g. flip3.engr.oregonstate.edu per the example above) or on a different machine   **
**  (e.g. flip2.oregonstate.edu). If executed on a different machine, steps 1 and 2     **
**  will need to be repeated on the second machine IF the directory used previously for **
**  storing the files is not accessible by the second machine. (More specifically, the  **
**  makefile and all files with file extensions ".c" or ".h" need to be present on the  **
**  machine running chatclient, whereon step 2 must be executed after the files are in  **
**  place, and all files with file extension .py need to be present on the machine      **
**  running chatserve.py, whereon step 2 is not required. However, as described above   **
**  steps 1 and 2 can be completed on both machines for simplicity. Finally, this note  ** 
**  can be ignored entirely if chatclient and chatserve.py are running on the same      **
**  machine.)                                                                           **
	
4.  If running chatclient on a different machine/server than chatserve, repeat steps 1
	  and 2 as needed on the second machine (see NOTE 1 above).
   
    Launch the c-based client (chatclient), specifying the server host name and port number on
	  the command line with program launch.
		~EX. To connect to the example server in step 3, 
			 where said example is running on flip3.engr.oregonstate.edu, 
			 type: "./chatclient flip3.engr.oregonstate.edu 35000" (without quotes)
			 
	You can optionally declare the client handle as a fourth command line argument.
		~EX. To connect to the example server in step 3, where said example is running on 
			 flip3.engr.oregonstate.edu, with client handle FRIDB, 
			 type: "./chatclient flip3.engr.oregonstate.edu 35000 FRIDB" (without quotes)
				- Client handle must be 10 characters or less
	
	If you do not declare a client handle at the command line with program launch, you will be
	  prompted to do so at program start up. (It is also optional to declare the server host
	  name and/or port number in the command line with program launch. Prompts at program
	  start up will be provided to determine unspecified parameters accordingly. Note that
	  command line arguments can not be specified out of order, and if any are omitted all
	  that follow must be omitted as well.)
	  
	If a successful connection is established, the message "Client: connecting to XXX.XXX.XXX.XXX"
	  will display, where "XXX.XXX.XXX.XXX" is the IP address of the server. This will be followed
	  by "You are now ready to chat!" and the client handle with "> " appended, each on its own new 
	  line. The server should now show the message "Connected: Waiting for response from 
	  XXX.XXX.XXX.XXX", where "XXX.XXX.XXX.XXX" is the IP address of the client.
	  
	If the connection is unsuccessful, you will likely see an error message and the program will
	  terminate. (It is likely the server will continue listening on the port specified in step 3
	  should this be the case.)
	  
5.  Rules of Chat
		i.   Messages must be sent in alternating fashion, starting with the client. 
			  (I.e. simultaneous sending/receiving is not supported.)
		
		ii.  The "active" host (or host "whose turn it is to send") will display its respective
			 handle as the last text printed to the console (followed by user input). The "passive"
			 host (or host "whose turn it is to receive") will display "**Connected: Waiting for
			 response from XXX.XXX.XXX.XXX" as the last text printed to its console, where 
			 XXX.XXX.XXX.XXX is the IP address of the sending (active) host. The sender inputs a
			 message (500 character max) and presses the "Enter" key to send the message, which
			 then displays on the receiver's console (prepended with the sender's handle), followed 
			 by the receiver's handle on a new line. The receiver then becomes the sender, and the
			 sender becomes the receiver.
			
		iii. A sending host can end the chat by typing "\quit" (without quotes). When this occurs,
			 a message will display on both client and server stating which host (client or server) 
			 ended the session. The server will then attempt to once more listen for incoming 
			 connections (chat requests) on the same port it used for the session just closed. If 
			 successful, it will once more display the message "Server Listening on Port: XXXXX". 
			 If unsuccessful, it will prompt the user to enter a new port. The client will then 
			 prompt the user to reconnect, establish a new connection, or quit. If the user elects 
			 to reconnect, the client will attempt to connect to the same server using the same port 
			 number and client handle. If the user elects for a new connection, new prompts will be 
			 issued to determine host server name, port number, and client handle. In either case, 
			 an unsuccessful connection will result in an error message and termination of the program. 
			 At any time, either server or client can terminate the program by holding down the "Ctrl" 
			 key and then pressing the "C" key.
			 
				- The typical test results showed that when the client ended the connection, the server
				  was able to successfully restablish the active ("listening") state using the same
				  port, after which the client could reconnect if its user so chose. However, if the 
				  server ended the connection, the port on which the server had been listening was not 
				  immediately available again and a new server port was needed.
				  
	  
!!!!! EXTRA CREDIT !!!!! - SENDING HOST'S INPUT DISPLAYS ON RECEIVING HOST'S CONSOLE AS IT IS TYPED
 
6.  If only the base program was compiled in step 2, type: "make chatclientEC" (without quotes)
	  Otherwise, skip this step.
	  
7.  Repeat steps 3 and 4, with the following exceptions:
		- Substitute "chatserveEC.py" for "chatserve.py"
		- Substitute "./chatclientEC" for "chatclient"
		
	Only the message "Connected to XXX.XXX.XXX.XXX" will display after successful connection
	  on both the server and the client, where XXX.XXX.XXX.XXX is the remote host's IP address.
		
8.  Rules of Chat
		i.   Same as base program (see step 5).
		
		ii.  The handle of the active (sending) host is displayed on both the server and
			 client consoles as the last output text (followed by sender input). As the sender 
			 types, both sender and receiver consoles will display sender input (note a possible 
			 delay on the receiving host due to network delays). When the sender presses "Enter", 
			 the active state is transferred to the remote host (i.e. sender becomes receiver, 
			 receiver becomes sender). The corresponding handle (i.e. new sender's handle) is 
			 displayed on a new line accordingly.
			 
		iii. Same as base program (see step 5), except the program cannot be terminated 
			 using "Ctrl+C" on the server side during the server's active (sending) state. 
			 Press "Enter" then "Ctrl+C" on the sender during its active state to terminate 
			 the program. (This does not apply to the client. "Ctrl+C" terminates program
			 client-side during either state.)
		
9.  To delete all object and executable files generated for the creation of chatclient
	  and/or chatclientEC, type: "make clean" (without quotes)
	  
**** Programs tested using various combinations of flip servers. 
**** Primarily used flip2.engr.oregonstate.edu for chatclient,
**** connected to chatserve.py running on flip3.engr.oregonstate.edu.