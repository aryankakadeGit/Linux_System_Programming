//CLIENT CODE

#include<stdio.h>       // for printf, scanf
#include<stdlib.h>      // for memory functions
#include<string.h>      // for memset

#include<unistd.h>      // for read, write, close
#include<fcntl.h>       // for file control

#include<sys/socket.h>  // for socket functions
#include<netinet/in.h>  // for sockaddr_in, htons

#include<arpa/inet.h>   // for inet_pton (IP conversion)


int main()                  // program starts
{
    int ServerSocketFD = 0; // client socket file descriptor
    int iRet = 0;           // store return values
    int Port = 11000;       // server port number


    struct sockaddr_in ServerAddr; // structure to store server IP and port

    char Buffer[1024] = {'\0'}; // buffer to receive server message


    //Step 1 :Create TCP Socket
    ServerSocketFD = socket(AF_INET,SOCK_STREAM,0); // create TCP socket

    if(ServerSocketFD < 0)  // if socket creation fails
    {
        printf("Unable to create socket :\n"); // error message
        return -1;          // exit
    }

    printf("Socket gets created succsfully  with fd: %d\n",ServerSocketFD); // success message

    

    //Step 2 :set memory to 0
    memset(&ServerAddr ,0,sizeof(ServerAddr)); // clear structure

    ServerAddr.sin_family = AF_INET;  // use IPv4
    ServerAddr.sin_port =  htons(Port); // convert port to network byte order

    //127.0.0.1-->binary from
    inet_pton(AF_INET,"127.0.0.1",&ServerAddr.sin_addr); // convert IP string to binary



    //Step 2 : Connect with Server
    iRet = connect(ServerSocketFD,(struct sockaddr*)&ServerAddr,sizeof(ServerAddr)); // connect to server

    if(iRet == -1)  // if connection fails
    {
        printf("Unable to connect with server:\n"); // error
        return -1;  // exit
    }

    printf("Client succesfully connected with server:\n"); // connection success



    //Step 3 :Read the data from Server
    iRet = read(ServerSocketFD,Buffer,sizeof(Buffer)-1); // read data from server

    if(iRet <= 0) // if read fails
    {
        printf("Unable to read the data from server:\n"); // error
        return -1; // exit
    }

    printf("Data from server is : %s\n",Buffer); // print received message



    //Step 4: close all resources
    close(ServerSocketFD); // close socket

    printf("Terminating the client application:\n"); // exit message

    return 0; // program ends
}

/*

    1. Buy phone (socket)
    2. Save friend's number (IP + Port)
    3. Dial number (connect)
    4. Listen message (read)
    5. Hang up (close)


*/
