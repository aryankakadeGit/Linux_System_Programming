//SERVER CODE


#include<stdio.h>       //prinf,scanf
#include<stdlib.h>      //malloc
#include<string.h>      //memcmp,memset

#include<unistd.h>      //MACRO,close,write,read
#include<fcntl.h>       //create.unlink,etc

#include<sys/socket.h>  //socket,bind,listen,accept,connect
#include<netinet/in.h>   //sockaddr_in ,htons

/*
struct sockaddr 
{
    sa_family_t sa_family;
    char sa_data[14];
}

*/

int main()
{

    int ServerSocket = 0;
    int iRet = 0;
    int Port = 11000;
    int ClientSocketFD = 0;


    struct sockaddr_in ServerAddr;

    //Step 1: Create TCP Socket

    ServerSocket = socket(AF_INET,SOCK_STREAM,0);

    if(ServerSocket < 0)
    {
        printf("Unable to create socket:\n");
        return -1;
    }
    
    printf("Socket gets created succesfully with fd : %d\n",ServerSocket);

    //Step 2 : Attch the Socket to IP Address and Port Number


    //Set memory with 0
    memset(&ServerAddr,0,sizeof(ServerAddr));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_family = INADDR_ANY;
    ServerAddr.sin_port =  htons(Port);
    

    iRet = bind(ServerSocket,(struct sockaddr*) &ServerAddr,sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Bind system call failed:\n");
        close(ServerSocket);
        return -1;
    }

    printf("Bind operation with socket is succesful\n");

    //Step 3 : Mark the socket as a active socket

    iRet = listen(ServerSocket,11);

    if(iRet == -1)
    {
        printf("Unable to convert socket in listen mode:\n");
        return -1;
    }

    printf("Server is live at port : %d\n",Port);

    //Step 4: Accept new socket request

    ClientSocketFD = accept(ServerSocket,NULL,NULL);

    if(ClientSocketFD == -1)
    {
        printf("Unable to accept request from client:\n");
        return -1;
    }

    printf("Request accepted by server:\n");

    return 0;
}