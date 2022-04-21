#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>

void printLoggedUsers()
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

void printLoggedUsersAndHost()
{
    struct utmpx *user;
    struct passwd * uid;
    user = getutxent();

    while(user)
    {
        if(user->ut_type == 7)
        {
            uid = getpwnam(user->ut_user);
            printf("login: %s host: %s \n", user->ut_user, user->ut_host);
        }
        user = getutxent();
    }
}