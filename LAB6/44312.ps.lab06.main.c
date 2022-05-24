// PS IN1 320 LAB05
// Karol Duszak
// dk44312@zut.edu.pl

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

void sig_kill_child_proces(int signum)
{
    if(signum == SIGALRM)
    {
        _exit(LIFE_TIME);
    }
}

void sig_action_handler(int no, siginfo_t *info, void *ucontext)
{
    printf("\nCtrl + C was pressed\n");
    KEEP_CREATING_NEW_CHILD=0;
}

int generateSubprocesses(int maxLifeTime)
{
    CHILD_COUNTER++;
    pid_t pid = fork();
    if(pid == 0)
    {
        LIFE_TIME = randomCalculationTime(maxLifeTime);
        time_t now = time(NULL);
        struct tm tm =*localtime(&now);
        printf("[%d] [%d] [%02d/%02d/%04d %02d:%02d:%02d]\n", getpid(), LIFE_TIME, tm.tm_mday, tm.tm_mon, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec);

        signal(SIGINT, SIG_IGN);
        signal(SIGALRM, sig_kill_child_proces);
        alarm(LIFE_TIME);
        calculateFactorial();
    }
    else if(pid < 0)
    {
        perror("fork error");
    }

    return 0;
}

void sig_child_proces_finished(int no, siginfo_t *info, void *ucontext)
{
    time_t now = time(NULL);
    struct tm tm =*localtime(&now);

    printf("\t\t\t\t[%d] [%d] [%02d/%02d/%04d %02d:%02d:%02d]\n", info->si_pid, info->si_status, tm.tm_mday, tm.tm_mon, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec);
    CHILD_COUNTER--;
}

int main(int argc, char** argv)
{
    //l <- thread life time
    //n <- number of threads
    int numberOfThreads=0, maxLifeTime=0;
    int opt;

    while ((opt = getopt(argc, argv, "l:n:")) != -1)
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
            case 'n':
                if(isNumber(optarg)==0)
                {
                    printf("Passed value for switch t is not a number: %s closing program\n", optarg);
                    exit(1);
                }
                char* cvalue = optarg;
                numberOfThreads = strtol(cvalue, NULL, 10);
                break;      
        }
    }

    return 0;
}