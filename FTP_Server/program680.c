#include<stdio.h>
#include<stdlib.h>

int main()
{
    printf("PID of running process :%d\n",getpid());

    printf("PPID of running process :%d\n",getppid());

    return 0;
}