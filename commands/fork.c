#include<stdio.h>
#include<wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>


void fun (int sig)
{
    printf("s=%d\n",sig);
    printf("child over!\n");
    int val=0;
    int id=wait(&val);
}


int main()
{
    int n=0;
    char *s=NULL;    
    pid_t pid=fork();
    if(pid==-1)
    {
        printf("fork error!!\n");
    }
    if(pid==0)
    {
        n=3;
        s="child";
    }
    else
    {
        n=7;
        s="parents";
        signal(SIGCHLD,fun);
    }
    for(int i=0;i<n;i++)
    {
        printf("s=%s\n",s);
       sleep(1);
    }
    exit(0);
}
