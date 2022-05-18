#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/types.h>

void userSpace()
{
    pid_t pid;
    pid = fork();
    printf("Pid: %d PPid: %d\n", getpid(), getppid());
}

void systemSpace()
{
    FILE *file;
    char buf[20];
    //clear file
    fclose(fopen("fileToWrite.txt", "w"));

    file =fopen("fileToWrite.txt", "w+");
    for(int i=0; i<10 ;i++)
    {
        fprintf(file, "Line %d added \n", i);
    }
    fclose(file);

    int fd;
    fd =open("fileToWrite.txt", O_RDONLY);
    read(fd,buf,20);
    //sleep(1);
    close(fd);
    printf("buf: %s\n", buf);

    // pid_t pid;
    // pid=fork();
    // int wstatus;
    // if(pid ==-1)
    // {
    //     fprintf(stderr,"Somethink went wrong on fork");
    // }
    // else if(pid>0)
    // {
    //     wait(&wstatus);
    // }
}

int main(int argc, char **argv)
{
    int opt;
    int fu=0; //flag user space
    int fs=0; //flag system space

    while ((opt = getopt(argc+1, argv, "eus")) != -1)
    {
        switch (opt)
        {
            case 'e':
                fprintf(stderr, "\nThis is message printed to sdterr\n");
                break;
            case 'u':
                userSpace();
                break;
            case 's':
                systemSpace();
                break;
            default:
                break;
        }
    }
    
    printf("\n");
}