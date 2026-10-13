//CLIENT CODE

#include<stdio.h>       //prinf,scanf
#include<stdlib.h>      //malloc
#include<string.h>      //memcmp,memset

#include<unistd.h>      //MACRO,close,write,read
#include<fcntl.h>       //create.unlink,etc

#include<sys/socket.h>  //socket,bind,listen,accept,connect
#include<netinet/in.h>   //sockaddr_in ,htons

#include<arpa/inet.h>


int main()
{
    int ServerSocketFD = 0;
    int iRet = 0;
    int Port = 11000;

    struct sockaddr_in ServerAddr;


    //Step 1 :Create TCP Socket

    ServerSocketFD = socket(AF_INET,SOCK_STREAM,0);

    if(ServerSocketFD < 0)
    {
        printf("Unable to create socket :\n");
        return -1;
    }

    printf("Socket gets created succsfully  with fd: %d\n",ServerSocketFD);

    
    //Step 2 :set memory to 0
    memset(&ServerAddr ,0,sizeof(ServerAddr));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port =  htons(Port);

    //127.0.0.1-->binary from
    inet_pton(AF_INET,"127.0.0.1",&ServerAddr.sin_addr);


    //Step 2 : Connect with Server
    iRet = connect(ServerSocketFD,(struct sockaddr*)&ServerAddr,sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Unable to connect with server:\n");
        return -1;
    }

    printf("Client succesfully connected with server:\n");
    

    return 0;
}