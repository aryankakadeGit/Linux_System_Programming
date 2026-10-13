//CLIENT APPLICATION


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

int ReadLine(int Sock , char *line,int max)
{

    int i = 0;
    char ch = '\0';
    int n = 0;

    while(i < max -1)
    {
        n = read(Sock, &ch , 1);

        if(n <= 0)
        {
            break;
        }

        line[i++] = ch;

        if(ch == '\n')
        {
            break;
        }
        
    }//End of while

    line[i] = '\0';

    return i;

}   //End of ReadLine

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      CommandLine Argument Application
//      1st Argument :  IP Address
//      2nd Argument : Port Number
//      3rd Argument : Target File Name
//      4th Argument : New File Name
//       
//          
//      ./client   127.0.0.1    9000     demo.txt   A.txt
//      argv[0]    argv[1]      argv[2]  argv[3]    argv[4]
//
//      argc = 5
//          
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc,char *argv[])
{   
    int Port = 0;   //argv[2]
    int Sock = 0;
    int iRet = 0;


    char *ip = NULL;            //argv[1]
    char *Filename = NULL;      //argv[3]
    char *Outfilename = NULL;    //argv[4]

    struct sockaddr_in ServerAddr;

    char Header[64] = {'\0'};

    
    if(argc < 5 || argc > 5)
    {
        printf("Unable to procced as invalid number of arguments:\n");

        printf("Please provide below arguments:\n");

        printf("1st Argument : IP Address\n");
        printf("2nd Argument : Port Number\n");
        printf("3rd Argument : Target File Name\n");
        printf("4th Argument : New File Name\n");

        return -1;
    }


    //store command line arguments into the variables
    ip = argv[1];
    Port = atoi(argv[2]);
    Filename = argv[3];
    Outfilename = argv[4];

    ///////////////////////////////////////////////////////////////////////
    //
    //  Step 1 : Create TCP Socket
    //
    /////////////////////////////////////////////////////////////////////////

    Sock = socket(AF_INET , SOCK_STREAM , 0);

    if(Sock < 0)
    {
        printf("Unable to create the client socket:\n");
        return -1;
    }


    ///////////////////////////////////////////////////////////////////////
    //
    //  Step 2 :  Connect with server
    //
    /////////////////////////////////////////////////////////////////////////

   memset(&ServerAddr,0,sizeof(ServerAddr));

   ServerAddr.sin_family = AF_INET;
   ServerAddr.sin_port = htons(Port);


   //Convert the IP Address into binary format

   inet_pton(AF_INET, ip,&ServerAddr.sin_addr);


    iRet = connect(Sock, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Unable to connect with server:\n");

        close(Sock);

        return -1;
    }

    ///////////////////////////////////////////////////////////////////////
    //
    //  Step 3 :  Send file name
    //
    /////////////////////////////////////////////////////////////////////////


    write(Sock,Filename,strlen(Filename));
    write(Sock,"\n",1);

    ///////////////////////////////////////////////////////////////////////
    //
    //  Step 4 : Read the Header
    //
    /////////////////////////////////////////////////////////////////////////

    iRet = ReadLine(Sock,Header, sizeof(Header));

    if(iRet <= 0)
    {
        printf("Server gets disconnected abnormally:\n");
        close(Sock);
        return -1;
    }

    long FileSize = 0;
    
    printf("Header is : %s\n",Header);

    sscanf(Header, "OK %ld",&FileSize);
    printf("File size  is: %ld\n",FileSize);

    ///////////////////////////////////////////////////////////////////////
    //
    //  Step 5 : create new file
    //
    /////////////////////////////////////////////////////////////////////////

    int Outfd = 0;

    Outfd =open(Outfilename, O_CREAT | O_WRONLY | O_TRUNC, 0777);

    if(Outfd < 0)
    {
        printf("Unable to create downloaded file:\n");
        return -1;
    }
    char Buffer[1024] = {'\0'};

    long Received =0;
    long Remaining = 0;

    int n = 0;
    int toRead = 0;

    while(Received < FileSize)
    {

        Remaining = FileSize - Received;

        if(Remaining > 1024)
        {
            toRead = 1024;
        }
        else
        {
            toRead = Remaining;
        }

        n = read(Sock,Buffer,toRead);

        write(Outfd,Buffer,n);

        Received = Received + n;
    }   //End of while

    close(Outfd);
    close(Sock);

    if(Received == FileSize)
    {
        printf("Download Complete....\n");
        return 0;
    }
    else
    {
        printf("Download Failed..\n");
        return -1;
    }
    
    return 0;
}//End of main