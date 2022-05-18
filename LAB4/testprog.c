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

void printMessageToStdErr()
{
    
}

int main(int argc, char **argv)
{
    int opt;
    int fu=0; //flag user space
    int fs=0; //flag system space

    while ((opt = getopt(argc+1, argv, "eus")) != -1)
    {
        printf("%d\n",opt);
        switch (opt)
        {
            case 'e':
                fprintf(stderr, "\nThis is message printed to sdterr\n");
                break;
            case 'u':
                fu=1;
                break;
            case 's':
                fs=1;
                break;
            default:
                break;
        }
    }

}