#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include "44312.ps.lab03.static.lib.h"

int main(int argc, char **argv)
{
    int fh=0, fg=0;
    int opt;
    while ((opt = getopt(argc, argv, "hg")) != -1)
    {
        switch (opt)
        {
        case 'h':
            fh = 1;
            break;
        case 'g':
            fg = 1;
            break;      
        }
    }

    if(fg == 1 && fh == 1)
    {
        printf("Tu 2 switche\n");
    }
    else if(fh == 1)
    {
        printLoggedUsersAndHost();
    }
    else if(fg == 1)
    {
        printf("Tu ma byc switch g");
    }
    else
    {
        printLoggedUsers();
    }

    return 0;
}