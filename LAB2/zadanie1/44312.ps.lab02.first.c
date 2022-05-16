#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <unistd.h>

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
    printf("\n %d %d \n", getpid(), getppid());

    return 0;
}