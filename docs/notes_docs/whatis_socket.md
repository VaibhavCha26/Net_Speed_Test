# What is Socket

## Random notes:
Basically everything is unix is a file :p duh - well basically what it means that any kind I/O done by programs is done by reading or writing "to a fd".

"fd" is not just files -- its any process, program, device, network connection or anything. -- wtf is FIFO ? --- so any interaction over the internet is done through a fd (fd in this case is the internet connection)

To get this fd for the connection i am gonna use the socket() system routine -- gives "Socket Descriptor" -- make use of it using things like send() or recv() -- (READ AND WRITE WORKS TOO !)

send--> {when the socket is connected and used to start the transmission from one socket to another socket}
recv --> {to receive message from both connected or not connec. socket. *does not permit the application to retrieve the source address of received data}
connect --> tries to make a connection on a connection-mode socket or set or reset the "other connection-less sockets address"

there are multiple sockets - INTERNET SOCKETS, UNIX SOCKETS, X.25 SOCKETS -- why ignore ??

1. STREAM SOCKETS {SOCK_STREAM}
2. DATAGRAM SOCKETS {SOCK_DGRAM} - can be connect()'d ???
3. MUCH MORE 

### 1.1 Stream sockets are "error-free" if sended 1,2 they will arrive 1,2 -- telnet / ssh use them too, HTTP Too.

### 1.2 stream sockets use TCP -- commonly called TCP/IP but ip here is for internet routing and is not responsible for data integrity

**** 

### 2.1 If data comes from datagram socket - it may arrive or it may  not arrive but if it arrives it will be error-free for sure.

### 2.2 Uses ip for routing too but uses the UDP

### 2.3 why connectionless ? basically it means that i don't have to maintain an open connection as i do with stream sockets. -- build a packet - slap a IP header (with destination information) on top of it and send it out. 
#### 2.3.1 used When tcp stack is unavailable or when a few dropped packets doesn't matter MUCH

### for unreliable application ?? - games audio or video - just ignore the dropped packets or compensate for them somehow (accursed lag) 

### 2.4 : why use it ? SPEEEEEEED -- Fire and forget instead of keeping track of what has arrived safely and making sure its in order and all that.

## DATA ENCAPSULATION 
[ETHERNET{ IP [ UDP { UDP [ TFTP { DATA }]}]}]
how SOCK_DGRAM packets are built --::>>

-- packet is born and its wrapped in a header by the first protocol which gets wrapped..... when another host receives it - it starts stripping the layers off -- now the ISO/OSI - it describes a system of network functionality that has many advantages over other models --- wtf ??? 
--


## Doubt
fd can be anything even a internet connection too -- then what is it basically at the low level ? is it a file or is it the process that the os is talking to ? Suppose a disk - then what does fd of disk mean - maybe a file (something that can be written or read from) containing the metadata or data of the file.

What is this X.25 sockets -- how do i make use of it.

Raw Sockets are powerful but what the hell are they ?

what does connectionless-mode and connected-mode even mean ??

what the fuck is telnet and what is GET / HTTP/1.0 .. hit enter twice

#### 2.3.1 --> its used in tftp(ttp clone ig?) and DHCPD use this -- but they are used to send binary applications to other host -- data must not be lost -- how can we afford to lose it ??

## Answers ig?
fd is just a integer -- the all is file abstraction is from VFS.fd is just a refrence that the os uses to look up the actual object ? -- > so like in case of write(fd) something - the kernel goes the network card driver which will put all of this into the network buffer.                                                 IN CASE OF FD OF DISK :: Points to a data structure that knows how to map the read write requests on a physical storage device.  So basically an integer pointing to the inode or vnode in storage block case ! -- its work is to guide the os to the inode and its done. !

#### 2.3.1A : Basically it has its own layer slapped over udp -- the ack packet -- acknowledgement stuff -- very important during implementation of SOCK_DGRAM.

