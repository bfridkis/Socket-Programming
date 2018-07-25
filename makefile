#CFLAGS = -g -Wall -std=gnu99
CFLAGS = -g -w -std=gnu99
VPATH = cutest

chatclient : chatclient.o get_in_addr.o bufferClear.o getServerName.o getServerPort.o getClientHandle.o
	gcc $(CFLAGS) -o $@ $^

chatclientEC : chatclientEC.o get_in_addr.o bufferClear.o getServerName.o getServerPort.o getClientHandle.o getch.o
	gcc $(CFLAGS) -o $@ $^

chatclient.o : chatclient.c
	gcc $(CFLAGS) -c -o $@ $<	
	
chatclientEC.o : chatclientEC.c
	gcc $(CFLAGS) -c -o $@ $<

get_in_addr.o : get_in_addr.c
	gcc $(CFLAGS) -c -o $@ $<
	
bufferClear.o : bufferClear.c
	gcc $(CFLAGS) -c -o $@ $<
	
getServerName.o : getServerName.c
	gcc $(CFLAGS) -c -o $@ $<
	
getServerPort.o : getServerPort.c
	gcc $(CFLAGS) -c -o $@ $<
	
getClientHandle.o : getClientHandle.c
	gcc $(CFLAGS) -c -o $@ $<
	
getch.o : getch.c
	gcc $(CFLAGS) -c -o $@ $<

memcheckProg : chatclient
	valgrind --tool=memcheck --leak-check=yes chatclient

all : chatclient chatclientEC
	
run :
	./chatclient
	
clean :
	-rm *.o
	-rm chatclient
	-rm chatclientEC
