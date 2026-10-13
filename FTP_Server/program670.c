//CLIENT CODE

#include<stdio.h>       //prinf,scanf
#include<stdlib.h>      //malloc
#include<string.h>      //memcmp,memset

#include<unistd.h>      //MACRO,close,write,read
#include<fcntl.h>       //create.unlink,etc

#include<sys/socket.h>  //socket,bind,listen,accept,connect
#include<netinet/in.h>   //sockaddr_in ,htons


int main()
{
    int ServerSocketFD = 0;

    //Step 1 :Create TCP Socket

    ServerSocketFD = socket(AF_INET,SOCK_STREAM,0);

    if(ServerSocketFD < 0)
    {
        printf("Unable to create socket :\n");
        return -1;
    }

    printf("Socket gets created succsfully  with fd: %d\n",ServerSocketFD);


    return 0;
}