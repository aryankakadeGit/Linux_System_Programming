//SERVER CODE

#include<stdio.h>       // for printf, scanf
#include<stdlib.h>      // for memory allocation and exit functions
#include<string.h>      // for memset, strlen

#include<unistd.h>      // for read, write, close system calls
#include<fcntl.h>       // for file control operations

#include<sys/socket.h>  // for socket related functions
#include<netinet/in.h>  // for sockaddr_in structure and htons

/*
struct sockaddr 
{
    sa_family_t sa_family;   // address family
    char sa_data[14];        // address data
}
*/

int main()                  // program starts
{

    int ServerSocket = 0;   // server socket file descriptor
    int iRet = 0;           // store return values
    int Port = 11000;       // port number for server
    int ClientSocketFD = 0; // client socket after accept

    struct sockaddr_in ServerAddr; // structure to hold IP and port

    char * message = "Jay Ganesh From Server\n"; // message to send client

    //Step 1: Create TCP Socket
    ServerSocket = socket(AF_INET,SOCK_STREAM,0); // create TCP socket

    if(ServerSocket < 0)      // if socket creation fails
    {
        printf("Unable to create socket:\n"); // print error
        return -1;            // exit
    }
    
    printf("Socket gets created succesfully with fd : %d\n",ServerSocket); // success message


    //Step 2 : Attch the Socket to IP Address and Port Number

    //Set memory with 0
    memset(&ServerAddr,0,sizeof(ServerAddr)); // clear structure

    ServerAddr.sin_family = AF_INET;  // use IPv4
    ServerAddr.sin_family = INADDR_ANY; // accept any IP  
    ServerAddr.sin_port =  htons(Port); // convert port to network byte order
    


    iRet = bind(ServerSocket,(struct sockaddr*) &ServerAddr,sizeof(ServerAddr)); // bind socket with address

    if(iRet == -1)           // if bind fails
    {
        printf("Bind system call failed:\n"); // error message
        close(ServerSocket); // close socket
        return -1;           // exit
    }


    printf("Bind operation with socket is succesful\n"); // bind success


    //Step 3 : Mark the socket as a active socket
    iRet = listen(ServerSocket,11); // listen for clients, queue size 11

    if(iRet == -1)         // if listen fails
    {
        printf("Unable to convert socket in listen mode:\n"); // error
        return -1;         // exit
    }

    printf("Server is live at port : %d\n",Port); // server ready message



    //Step 4: Accept new socket request
    ClientSocketFD = accept(ServerSocket,NULL,NULL); // accept client

    if(ClientSocketFD == -1) // if accept fails
    {
        printf("Unable to accept request from client:\n"); // error
        return -1;          // exit
    }

    printf("Request accepted by server:\n"); // connection success



    // Step 5: Send the message to client
    write(ClientSocketFD,message,strlen(message)); // send message to client


    //Step 6: Close all resources
    close(ClientSocketFD); // close client socket
    close(ServerSocket);   // close server socket

    printf("Terminating server application:\n"); // exit message

    return 0; // program ends
}

/*
    Think of it is Like:

    socket() → buying a mobile phone

    bind() → inserting SIM + getting phone number

    listen() → waiting for calls

    accept() → answering call

    Without SIM (bind), nobody can call you.

------------------------------------------------------

    1. Buy phone (socket)
    2. Get SIM with number (bind)
    3. Wait for calls (listen)
    4. Answer call (accept)
    5. Speak message (write)
    6. Hang up (close)

*/
