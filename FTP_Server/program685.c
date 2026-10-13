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

    char FileName[50] = {'\0'};

    pid_t pid = 0;
    

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


    //////////////////////////////////////////////////////////////////////
    //
    //  Loop Which Accepts client request continuosly
    //
    ///////////////////////////////////////////////////////////////////////


    //Loop to accept multiple client request
    while(1)
    {

        //////////////////////////////////////////////////////////////////////
        //
        //  Step 4 : Accept the client request
        //
        ///////////////////////////////////////////////////////////////////////

        memset(&CilentAddr,0,sizeof(CilentAddr));

        printf("Server is waiting for client request\n");

        ClientSocket = accept(ServerSocket , (struct sockaddr *)&CilentAddr, &AddrLen);

        if(ClientSocket < 0)
        {
            printf("Unable to accept client request:\n");

            continue; //For while

        }

        printf("Client gets connected : %s\n",inet_ntoa(CilentAddr.sin_addr));


        //////////////////////////////////////////////////////////////////////
        //
        //  Step 5 : Create new process to handle client request
        //
        ///////////////////////////////////////////////////////////////////////

        pid = fork();

        if(pid < 0)
        {
            printf("Unable to crete a new process for client request:\n");

            close(ClientSocket);

            continue;
        }


        //New process gets created for client
        if(pid == 0)
        {
            printf("New process is created for client request:\n");

            close(ServerSocket);

            //printf("%d\n",ClientSocket);


            iRet = read(ClientSocket,FileName,sizeof(FileName));

            printf("Requested file by client:  %s\n",FileName);

            break;


        
        }



    } //End of while

    
    return 0;
}//End of main