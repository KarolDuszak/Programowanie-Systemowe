#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include "44312.ps.lab03.static.lib.h"

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "hg")) != -1)
    {
        switch (opt)
        {
        case 'h':
            printLoggedUsers();
            break;
        case 'g':
            printLoggedUsersAndHost();
            break;
        case '?':
            printf("lol nie dziala \n");
            break;            
        default:
            abort();
        }
    }

    return 0;
}