// PS IN1 320 LAB04
// Karol Duszak
// dk44312@zut.edu.pl

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


char* hashPassword(char* password, char* salt)
{
    return "a";
}

int main(int argc, char **argv)
{
    char* password=NULL;
    char* salt=NULL;
    int opt;

    while ((opt = getopt(argc, argv, "s:p:")) != -1)
    {
        switch (opt)
        {
        case 's':
            salt = optarg;
            break;
        case 'p':
            password = optarg;
            break;
        }
    }

    printf("Password: %s Salt: %s\n", password, salt);
    char * hash= hashPassword(password, salt);
    printf("Hash: \n%s\n", hash);
}