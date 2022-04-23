#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include "44312.ps.lab03.static.lib.h"
#include <string.h>

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
        printLoggedUsersHostsAndGroupList();
    }
    else if(fh == 1)
    {
        printLoggedUsersAndHost();
    }
    else if(fg == 1)
    {
        char ** grupa;
        struct utmpx *user;
        struct passwd * uid;
        user = getutxent();

        while(user)
        {
            if(user->ut_type == 7)
            {
                printf("User: %s Groups:", user->ut_user);
                uid = getpwnam(user->ut_user);
                grupa = getLoggedUsersAndGroupList(user);
                for(int i=0; i<sizeof(grupa)+1; i++)
                {
                    printf(" %s,", grupa[i]);
                }
                printf("\n");
            }
            user = getutxent();
        }
        free(grupa);
    }
    else
    {
        printLoggedUsers();
    }

    return 0;
}