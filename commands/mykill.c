#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
   if(argc!=3)
   {
    printf("argv error!\n"); 
   }
   int pid=0;
   int sig=0;
   sscanf(argv[1],"%d",&pid);
   sscanf(argv[2],"%d",&sig);
   if(kill(pid,sig)==-1)
   {
       printf("kill error!\n");
   }
   
    exit(0);
}
