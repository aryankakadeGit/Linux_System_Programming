//SERVER APPLICATION


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdbool.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      CommandLine Argument Application
//      1st Argument : Port Number
//
//      ./server   9000
//      argv[0]    argv[1]
//      
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc,char *argv[])
{   
    
    int ServerSocket = 0;
    int ClientSocket = 0;
    int Port = 0;
    int iRet = 0;
    

    struct sockaddr_in ServerAddr;
    struct sockaddr_in CilentAddr;


    socklen_t AddrLen = sizeof(ClientSocket);


    if((argc < 2) || (argc > 2))
    {
        printf("Unable to proceed as invalid number of arguments:\n");
        printf("Please provide the port number:\n");

        return -1;
    }

    //port number of server
    Port = atoi(argv[1]);

    
    //////////////////////////////////////////////////////////////////////
    //
    //  Step 1 :Create TCP Socket
    //
    ///////////////////////////////////////////////////////////////////////


    ServerSocket = socket(AF_INET ,SOCK_STREAM,0);

    if(ServerSocket  < 0)
    {
        printf("Unable to create server socket :\n");
        return -1;
    }

    //////////////////////////////////////////////////////////////////////
    //
    //  Step 2 : Bind socket to IP and Port
    //
    ///////////////////////////////////////////////////////////////////////

    memset(&ServerAddr,0,sizeof(ServerAddr));


    //Initialize the structure

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);
    ServerAddr.sin_addr.s_addr = INADDR_ANY;

    iRet = bind(ServerSocket, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Unable to bind:\n");
        close(ServerSocket);

        return -1;
    }

    //////////////////////////////////////////////////////////////////////
    //
    //  Step 3 : Listen for client connections
    //
    ///////////////////////////////////////////////////////////////////////

    iRet = listen(ServerSocket,11);

    if(iRet == -1)
    {
        printf("Server to Unable to listen:\n");
        close(ServerSocket);

        return -1;
    }
    

    printf("Server is Running on port %d\n",Port);
    
    return 0;
}