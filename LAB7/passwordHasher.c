// PS IN1 320 LAB07
// Karol Duszak
// dk44312@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>


char* hashPassword(char* password, char* salt)
{    
    size_t len;
    char* encrypted;
    len = strlen(salt);
    char salt2[len+3];
    strcpy(salt2,"$6$");
    strcat(salt2, salt);
    printf("%s", salt2);
    
    encrypted = crypt(password, salt2);
    return encrypted;
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