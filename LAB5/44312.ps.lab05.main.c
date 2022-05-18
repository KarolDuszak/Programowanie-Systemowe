#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>

int LIFE_TIME =0;

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
    printf("Result: %ld", result);
}

int randomCalculationTime(int max)
{
    srand(time(0));
    int result = rand()%max+1;
    return result;
}

void sig_kill_child_proces(int signum)
{
    if(signum == SIGALRM)
    {
        //jak przekazac lifeTime tutaj?
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
    
}

void generateSubprocesses(int interval)
{
    signal(SIGALRM, sig_handler);
    alarm(interval);

}

int main(int argc, char** argv)
{
    //l <- subprocess life time
    //c <- subprocess creation time
    int timeToCreate=0, maxLifeTime=0;
    int opt;
    struct sigaction sa;
    sa.sa_sigaction = sig_action_handler;


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

    int timeOfCalculation = randomCalculationTime(maxLifeTime);

    //calculateFactorial();
    return 0;
}