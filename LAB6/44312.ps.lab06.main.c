// PS IN1 320 LAB06
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
#include "44312.ps.lab06.timer.h"
#include <pthread.h>

struct threadData{
    pthread_t thread;
    int lifetime;
};
static pthread_key_t stopCalculatingKey;
static pthread_once_t stopCalculatingOnce = PTHREAD_ONCE_INIT;

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

void sig_end_thread(int signal)
{
    if(signal == SIGUSR1)
    {
        int* stopCalculating = pthread_getspecific(stopCalculatingKey);
        *stopCalculating = 1;
    }
}

static int compare(const void *p1, const void *p2)
{
    struct threadData *e1 = (struct threadData *)p1;
    struct threadData *e2 = (struct threadData *)p2;

    if(e1->lifetime < e2->lifetime)
        return -1;
    else if(e1->lifetime>e2->lifetime)
        return 1;
    else
        return 0;
}
static void freeMemory(void *buffer)
{
    free(buffer);
}

static void createKey(void)
{
    pthread_key_create(&stopCalculatingKey, freeMemory);
}

void* executeThread(void* flag)
{
    startTimer();
    int *counter;
    //utoworzenie klucz dla specyficznych danych przy pierwszym wywoalaniu
    pthread_once(&stopCalculatingOnce, createKey);

    //pobranie pamieci powiazanej z kluczem
    counter = pthread_getspecific(stopCalculatingKey);
    // przy 1 wywoaniu zaalokuj pamiec i powiaz z kluczem
    if(counter == NULL)
    {
        counter= malloc(sizeof(int));
        *counter = 0;
        pthread_setspecific(stopCalculatingKey, counter);
    }

    unsigned long result=1;
    unsigned int value =1;

    while(*counter==0)
    {
        result = result * value;
        value++;
        if(result == 0){
            result=1;
        }
    }
    int timeStamp = stopTimer();
    printf("TID: %ld Time: %d\n", pthread_self(), timeStamp);
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

    struct threadData threads[numberOfThreads];
    struct sigaction act;
    act.sa_handler = sig_end_thread;
    act.sa_flags=0;
    sigemptyset(&(act.sa_mask));
    sigaction(SIGUSR1, &act, NULL);

    for(int i=0; i<numberOfThreads;i++)
    {
        threads[i].lifetime = randomCalculationTime(maxLifeTime);
        usleep(598200); //Za szybko sie tworza wiec zeby zroznicowac czasy umiescilem sleep bo wszystkie mialy taki sam czas
    }

    for(int i=0; i<numberOfThreads;i++)
    {
        int status = pthread_create(&threads[i].thread, NULL, executeThread, NULL);
        printf("Tid: %ld life time: %d\n", threads[i].thread, threads[i].lifetime);
    }

    qsort(&threads, numberOfThreads,sizeof(struct threadData), compare);

    int timer=0;
    for(int i=0; i<numberOfThreads; i++)
    {
        int timeLeftToWait = threads[i].lifetime - timer;
        if(timeLeftToWait > 0)
        {
            int left = sleep(timeLeftToWait);
            while(left!=0)
                left = sleep(left);
        }
        pthread_kill(threads[i].thread, SIGUSR1);
        timer += timeLeftToWait;
        //pthread_join(threads[i].thread, NULL);
    }

    for(int i=0; i<numberOfThreads; i++)
    {
        pthread_cancel(threads[i].thread);
        pthread_join(threads[i].thread, NULL);
    }

    return 0;
}