// PS IN1 320 LAB03
// Karol Duszak
// dk44312@zut.edu.pl

#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>

void ( *printLoggedUsers);
void ( *printLoggedUsersAndHost);
char** ( *getLoggedUsersAndGroupList)(struct utmpx*, int* count);
void ( *printLoggedUsersHostsAndGroupList);

int main(int argc, char **argv)
{
    int fh=0, fg=0;
    int opt;

    void *handle = dlopen("./44312.ps.lab03.shared.lib.so.0.1", RTLD_LAZY);
    if(!handle)
    {
        printf("Lib not loaded");
        dlerror();
    }
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
        if(!handle)
        {
            printf("Lib not found");
            struct utmpx *user;
            struct passwd * uid;
            user = getutxent();

            while(user)
            {
                if(user->ut_type == 7)
                {
                    uid = getpwnam(user->ut_user);
                    printf("login: %s \n", user->ut_user);
                }
                user = getutxent();
            }
        }
        else{
            void (*printing)(void) = dlsym(handle, "printLoggedUsersHostsAndGroupList");
            printing();
            dlclose(handle);
        }
    }
    else if(fh == 1)
    {
        if(!handle)
        {
            printf("Lib not found");
            struct utmpx *user;
            struct passwd * uid;
            user = getutxent();

            while(user)
            {
                if(user->ut_type == 7)
                {
                    uid = getpwnam(user->ut_user);
                    printf("login: %s \n", user->ut_user);
                }
                user = getutxent();
            }
        }
        else{
            void (*printing)(void)= dlsym(handle, "printLoggedUsersAndHost");
            printing();
            dlclose(handle);
        }
    }
    else if(fg == 1)
    {
        if(!handle)
        {
            printf("Lib not found");
            struct utmpx *user;
            struct passwd * uid;
            user = getutxent();

            while(user)
            {
                if(user->ut_type == 7)
                {
                    uid = getpwnam(user->ut_user);
                    printf("login: %s \n", user->ut_user);
                }
                user = getutxent();
            }
        }
        else{
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
                    getLoggedUsersAndGroupList = dlsym(handle, "getLoggedUsersAndGroupList");
                    int numOfGroups = 0;
                    grupa = getLoggedUsersAndGroupList(user, &numOfGroups);
                    dlclose(handle);
                    for(int i=0; i<numOfGroups; i++)
                    {
                        printf(" %s,", grupa[i]);
                    }
                    printf("\n");
                }
                user = getutxent();
            }
        free(grupa);
        }
    }
    else
    {
        struct utmpx *user;
        struct passwd * uid;
        user = getutxent();

        while(user)
        {
            if(user->ut_type == 7)
            {
                uid = getpwnam(user->ut_user);
                printf("login: %s \n", user->ut_user);
            }
            user = getutxent();
        }
    }

    return 0;
}