#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>

int LIFE_TIME = 0;
int KEEP_CREATING_NEW_CHILD = 1;
int CHILD_COUNTER = 0;

int isNumber(char *number)
{
    size_t len = sizeof(number)/sizeof(number[0]);

    for(int i=0; i<len; i++)
    {
        if(!isdigit(number[i]))
        {
            if(number[i] == 0)
            {
                break; //When it is null then all passed params were checked
            }
            //printf("This is not a digit: %d\n", number[i]);
            return 0;
        }
        //printf("This is a digit %c\n", number[i]);
    }
    return 1;
}

int calculateFactorial()
{
    unsigned long result=1;
    unsigned int value =1;

    while(1)
    {
        result = result * value;
        value++;
        if(result== 0){
            result=1;
        }
    }
    //printf("Result: %ld", result);
}

int randomCalculationTime(int max)
{
    srand(time(0));
    int result = rand()%max+1;
    return result;
}
int isAnyChildActive()
{
    if(CHILD_COUNTER == 0)
    {
        return 0;
    }
    return 1;
}

void sig_kill_child_proces(int signum)
{
    if(signum == SIGALRM)
    {
        _exit(LIFE_TIME);
    }
}

void sig_generate_Subprocess(int maxLifeTime)
{
    LIFE_TIME = randomCalculationTime(maxLifeTime);
    signal(SIGALRM, sig_kill_child_proces);
    alarm(LIFE_TIME);

}

void sig_action_handler(int no, siginfo_t *info, void *ucontext)
{
    printf("\nCtrl + C was pressed\n");
    KEEP_CREATING_NEW_CHILD=0;
}

int generateSubprocesses(int maxLifeTime)
{
    int lifeTime = randomCalculationTime(maxLifeTime);
    
    CHILD_COUNTER++;
    pid_t pid = fork();

    if(pid == 0)
    {
        //signal(SIGINT, SIG_IGN);
        signal(SIGALRM, sig_kill_child_proces);
        alarm(lifeTime);
        calculateFactorial();
        CHILD_COUNTER--;
        printf("lifetime: %d\n", lifeTime);
        return lifeTime;
    }
    else if(pid < 0)
    {
        perror("fork error");
    }
    else{

    }

    return 0;
}

int main(int argc, char** argv)
{
    //l <- subprocess life time
    //c <- subprocess creation time
    int timeToCreate=0, maxLifeTime=0;
    int opt;
    struct sigaction sa;
    sa.sa_sigaction = sig_action_handler;
    sigemptyset(&(sa.sa_mask));
    sa.sa_flags=SA_SIGINFO;
    int x = sigaction(SIGINT, &sa, NULL);

    while ((opt = getopt(argc, argv, "l:c:")) != -1)
    {
        switch (opt)
        {
            case 'l':
                if(isNumber(optarg)==0)
                {
                    printf("Passed value for switch t is not a number: %s closing program\n", optarg);
                    exit(1);
                }
                char* lvalue = optarg;
                maxLifeTime = strtol(lvalue, NULL, 10);
                break;
            case 'c':
                if(isNumber(optarg)==0)
                {
                    printf("Passed value for switch t is not a number: %s closing program\n", optarg);
                    exit(1);
                }
                char* cvalue = optarg;
                timeToCreate = strtol(cvalue, NULL, 10);
                break;      
        }
    }

    while(KEEP_CREATING_NEW_CHILD)
    {
        int procesType = generateSubprocesses(maxLifeTime);
        if(procesType !=0)
        {
            printf("Calculations were made for: %ds\n", procesType);
        }
        sleep(timeToCreate);
    }

    while(isAnyChildActive() == 1);

    return 0;
}