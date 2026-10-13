#include<stdio.h>

int main(int argc,char *argv[])
{   
    printf("Number of command line argument are: %d\n",argc);

    printf("Executable Name : %s\n",argv[0]);
    printf("IP Address :%s\n",argv[1]);
    printf("Port Number:%s\n",argv[2]);
    printf("Targeted File :%s\n",argv[3]);
    printf("New File Name :%s\n",argv[4]);
    
    return 0;
}