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

### 3.4 : why use it ? SPEEEEEEED -- Fire and forget instead of keeping track of what has arrived safely and making sure its in order and all that.

## DATA ENCAPSULATION 
[ETHERNET{ IP [ UDP { UDP [ TFTP { DATA }]}]}]
how SOCK_DGRAM packets are built --::>>

-- 
packet is born and its wrapped in a header by the first protocol which gets wrapped..... when another host receives it - it starts stripping the layers off -- now the ISO/OSI - it describes a system of network functionality that has many advantages over other models --- wtf ???
--

i can write the programs that are exactly the same without caring out how the data is physically transmitted.so the actual hardware shit is unknown to me always.


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







# PRACTICAL STUFF I GUESS 
00. WIFI_CARD:
  00.1 : no idea wtf this niga is - it only understands raw packets that is and it does something related to transmission of stuff -- final form.

0. SOCKET()
  0.1 : A real structure inside the computers ram -- when socket is called - the os allocates a physical chunk of memory to make a "SOCKET DATA STRUCTURE" 
    ---> listening, closed, connected, ip and port number, buffers (for inbox and outbox) 
    
    ---> the socket data structure is stored in Kernel Space RAM;
  0.2 : Kernel acts as middlemen (constantly checks memory before calling wifi card) - kernel's networking subsystem continuously monitors all active socket data structures. -- when the kernel sees data sitting in sockets outbox it pulls that data out - stamps it and viola - calls the driver -- "send this data bitch"
    
    0.2.1 : BUFFERS ARE SHOCK ABSORBERS -- the internet is chaotic :O - packets get dropped, wifi stops or something and stuff 
    -- important: CAN BYPASS IT by disabling the **NAGLE ALGORITHM** (TCP_NODELAY) ---
      
      A. kernel operates on NAGLE ALGORITHM








1. SEND() AND RECV()

  1.1 to measure the wifi data speed i need to send() over and over again -- so basically dump lots of data to the buffer (100mb or smth) as fast as possible (wtf ?).
    
      1.1.1 : so when everything is dumped into the buffer the wifi card or mail carrier will take handful of data - make a 'network packet' and then drops them into receivers mailbox.
      1.1.2 : don't worry about flow and all that - kernel automatically calls wait() and automatically restarts the program so the cpu overhead is 0%

      1.1.3 : so yes it does memory copy -- exactly how ? idk T-T - kernel copies the bytes memory space into the sockets buffer memory space inside the kernel and once its done - change whatever you want;
         
        1.1.3.1 : so the buffer (the outputbox buffer) is strictly limited - the point is that send call won't complete until the entire data is copied and sended over the wifi card !! -- so the question that what if i change the memory is not in the buffer is idiotic T-T.
          
          1.1.3.1.1 : so there's something like "zero copy" / asynchronous sockets where kernel skips buffer and reads straight from variable (wtf ? -- advanced stuff !! T-T)
          
          1.1.3.1.2 : so in single threaded program it is impossible because my program stops when send() call is running. However in multi threaded program it is possible that thread a calls send and thread b forcefully overwrites the contents of the buffer.
****



  1.2 Call recv() repeatedly to such that data from the inbox until its all gone ? { sending to a buffer because cpu is too fast for the wifi card } -- then stop the timer. 
    
    1.2.1: if inbox is empty the recv() WAITS until the data arrives over the wifi.
    1.2.2 idiocy : after taking the data from inbox buffer it takes the data to an internal buffer wtf ?
    1.2.3 : It can't random data floating in the air - it requires a handshake (wtf) 
      ---> (sender) opens the socket and tells the os that i am going to listen some port.
      ---> (receivers) call the machine at 1.1.1.1 on that port ?
    
#### some dance called tcp handshake wtf ?
    1.2.4 in case of other machines it works exactly the smae xP thanks to global routing ? - does syn -ack 3 way handshake and then virtual pipe is intialized 
      1.2.4.1 : once the handshake is done both os have matching socket structures in their respective kernels - pipe is "just an agreement between kernel to talk to each other"

****



2. DOWNLOAD SPEED TEST : 
  A. send the dummy data (its basically chunk of random memory ) into its buffer and network starts streaming it as fast as it can (where though?). 
  B. start a stopwatch the exact moment the data lands into the buffer and then loop it until it returns 0 and then stop the timer (do the math and done)
  B.1 : the data that we get from inbox buffer gets into an internal buffer -- overwrite that as its useless.

### * B.2 : NO MULTIPLE SOCKETS -- single socket - its like a connection not a packet - so stream million gb if you want to.
  
  B.3 : HOW to keep each data separate ? 
      --> THE KERNEL STAMPS IT : so basically it has 4-part address ( called "tuple" ) source ip, source port, destination ip, destination port.
    
    B.3.1 : PORT --> basically if there were no ports (its just a stamp on the data at the end of the data everything is done by wifi card) the data of 500 bytes will come but the kernel will have no idea which process needs this or anything. ( JUST A NUMBER )
