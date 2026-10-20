#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    execlp("ps","ps","-f",(char *)0);
    exit(0);
}
