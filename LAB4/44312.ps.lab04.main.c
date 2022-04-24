#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    int fv=0, ft=0;
    int opt;

    for(int i=0; i< argc ; i++)
    {
        printf("%s \n", argv[i]);
    }
    while ((opt = getopt(argc, argv, "+vt:")) != -1)
    {
        //char x = opt;
        //printf("%c \n",x);
        switch (opt)
        {
        case 'v':
            fv = 1;
            printf("flaga v");
            break;
        case 't':
        //Konwersja na int ze stringa
    
            ft = 1;
            char* tvalue = optarg;
            long tNumber = strtol(tvalue, NULL, 10);

            tNumber = tNumber +1;
            printf("flaga t %s %ld", tvalue, tNumber);
            break;      
        }
    }
    return 0;
}

int isNumber(char *number)
{
    size_t len = sizeof(number)/sizeof(number[0]);

    for(int i=0; i<len; i++)
    {
        if(!isdigit(number[i]))
        {
            return 0;
        }
    }
    return 1;
}