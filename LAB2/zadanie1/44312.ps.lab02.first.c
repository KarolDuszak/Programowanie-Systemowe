#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>

int main(void)
{
    struct utmpx *a;
    struct passwd * b;
    a = getutxent();

    while(a)
    {
        if(a->ut_type == 7)
        {
            b = getpwnam(a->ut_user);
            printf("uid: %i login: %s \n", b->pw_uid, a->ut_user);
        }
        a = getutxent();
    }

    return 0;
}