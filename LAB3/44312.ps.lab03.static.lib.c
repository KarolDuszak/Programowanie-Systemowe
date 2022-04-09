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
            printf("uid: %i login: %s \n", uid->pw_uid, user->ut_user);
        }
        user = getutxent();
    }
}