#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<assert.h>
#include<string.h>
#define ARG_MAX 10
#include<pwd.h>
#define PATH_BIN  "/home/stu/class03/test15/mybin/"
void printf_info()
{
    char *user_str="$";
    int user_id=getuid();
    if(user_id==0)
    {
        user_str="#";
    }
    struct passwd *ptr=getpwuid(user_id);
    if(ptr==NULL)
    {
    
        printf("mybash1.0>> error");
        fflush(stdout);
        return ;
    }
    char hostname[128]={0};
    if(gethostname(hostname,128)==-1)
    {
        printf("Mybash1,0>>");
        fflush(stdout);
        return ;
    }
    char dir[256]={0};
    if(getcwd(dir,256)==NULL)
    {
    
        printf("Mybash1,0>>");
        fflush(stdout);
        return ;
    }
    printf("\033[1;32m %s@%s\033[0m     \033[1;34m%s\033[0m%s ",ptr->pw_name,hostname,dir,user_str);
    fflush(stdout);
}
char *get_cmd(char *buff, char * myargv[])
{
    if (buff==NULL||myargv==NULL)
    {
     return NULL;
    }
    int i=0;
  char * s=strtok(buff," ");
  while(s!=NULL)
  {
    myargv[i++]=s;
     s=strtok(NULL," ");
  }
    return myargv[0];
}

void  run_cmd(char *pash ,char *myargv[])
{
    if(pash==NULL||myargv==NULL)
    {
        return ;
    }

    pid_t pid =fork();
    if (pid==-1)
    {
        return ;
    }
    if(pid==0)
    {
       // execvp(pash,myargv);
       // perror("execvp error!!!");
       // exit(0);
        char pathname[128]={0};
        if(strncmp(pash,"/",1)==0||strncmp(pash,"./",2)==0)
        {
          strcpy(pathname,pash);
        }
        else
        {
         strcpy(pathname,PATH_BIN);
         strcat(pathname,pash);
         }
       execv(pathname,myargv);    
        perror("execvp error!!!");
        exit(0);
    }
    else
    {
        wait(NULL);
    }
}

int main()
{
    while(1)
    {

        printf_info();
           // printf("stu@loacalhost   ~$");
          //fflush(stdout);//刷新，输出缓冲区。
        char buff[128]={0};
         fgets(buff,128,stdin);
       buff[strlen(buff)-1]='\0'; 
         char *myargv[ARG_MAX]={0};
         char *cmd=get_cmd(buff,myargv);
         if (cmd==NULL)
         {
           continue;
         }
         else if(strcmp(cmd,"cd")==0)
         {
             if(myargv[1]!=NULL)
             {
                    if(chdir(myargv[1])==-1)
                     {
                       perror("cd err\n");    
                     }
             
             }
    
         }
         else if(strcmp(cmd,"exit")==0)
         {
            break;
         }   
         else 
         {
            //fork+exec
            run_cmd(cmd,myargv);
         }
        
    }
    
    exit(0);
    
}
