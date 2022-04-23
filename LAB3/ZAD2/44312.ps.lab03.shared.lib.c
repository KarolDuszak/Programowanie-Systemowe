#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <grp.h>
#include <string.h>

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

char** getLoggedUsersAndGroupList(struct utmpx * user, int* count)
{
    struct passwd * uid;
    int ngroups=50;
    struct group *gr;
    gid_t * groups = malloc(sizeof(*groups) * ngroups);
    char ** names;

    uid = getpwnam(user->ut_user);
    if(getgrouplist(user->ut_user, uid->pw_gid, groups, &ngroups)== -1)
    {
        printf("User is member of more than 50 groups");
        exit(EXIT_FAILURE);
    }
    int size=0;
    for(int j=0; j<ngroups; j++)
    {
        gr = getgrgid(groups[j]);
        if(gr != NULL)
        {
            size++;
        }
    }
    *count = size;
    names = malloc(sizeof(char*)*size);

    int j=0;
    for(int i=0; i< ngroups; i++)
    {
        gr = getgrgid(groups[i]);
        if(gr != NULL)
        {
            names[j] = malloc(sizeof(char*) * (strlen(gr->gr_name)+1));
            strncpy(names[j], gr->gr_name, strlen(gr->gr_name)+1);
            j++;
        }
    }
    free(groups);
    return(names);
}

void printLoggedUsersHostsAndGroupList()
{
    struct utmpx *user;
    struct passwd * uid;
    user = getutxent();
    char ** grupa;

    while(user)
    {
        if(user->ut_type == 7)
        {
            uid = getpwnam(user->ut_user);
            printf("login: %s host: %s groups: ", user->ut_user, user->ut_host);
            int numOfGroups =0;
            grupa = getLoggedUsersAndGroupList(user, &numOfGroups);
            for(int i=0; i<numOfGroups; i++)
            {
                printf(" %s,", grupa[i]);
            }
            printf("\n");
        }
        user = getutxent();
    }
}