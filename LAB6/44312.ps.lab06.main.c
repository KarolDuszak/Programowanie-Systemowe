// PS IN1 320 LAB06
// Karol Duszak
// dk44312@zut.edu.pl

#define _GNU_SOURCE
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
    int keepCalculating;
};

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

void* executeThread(void* flag)
{
    printf("TID: %ld\n", pthread_self());
    
    unsigned long result=1;
    unsigned int value =1;

    while(*(int*)flag==1)
    {
        result = result * value;
        value++;
        if(result== 0){
            result=1;
        }
    }
    printf("KONIEC \n");
}

int sig_end_thread(const int signal, int* ptr)
{
    int * saved = NULL;
    if(saved==NULL)
    {
        saved=ptr;
    }
    if(signal == SIGALRM)
    {
        *saved=0;
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
    //act.sa_sigaction = sig_end_thread;
    
    //sigaction(SIGALRM, &act, NULL);
    signal(SIGALRM, (void(*)(int)) sig_end_thread);
    for(int i=0; i<numberOfThreads;i++)
    {
        threads[i].keepCalculating=1;
        printf("Pointer: %ls", &threads[i].keepCalculating);
        int status = pthread_create(&threads[i].thread, NULL, executeThread, &threads[i].keepCalculating);
        threads[i].lifetime = randomCalculationTime(maxLifeTime);
        printf("status: %d id: %ld life time: %d\n", status, threads[i].thread, threads[i].lifetime);
        sig_end_thread(SIGUSR1, &threads[i].keepCalculating);
        //alarm(threads[i].lifetime);
        sleep(1); //Za szybko sie tworza wiec zeby zroznicowac czasy umiescilem sleep bo wszystkie mialy taki sam czas

    }

    qsort(&threads, numberOfThreads,sizeof(struct threadData), compare);
    //pthread_kill moze sygnal wyslac wybrany a tam juz mozna obsluzyc xDDD

    // Teraz to musi by wywolywane przez sygnal
    // trzeba mu przekazac jakos ta strukture
    // przy tworzeniu zeby set alarm a jak alarm sie odpali to zabic ten proces
    // mozna przekazac id np lub wskaznik i wtedy go zabic
    

    //alarm(threads[i].lifetime);
    // moze trzymac ilosc aktywynych watkow zeby program zakonczyc dopiero jak
    // wszystkie zostana ubite?
    sleep(5);
    //threads[0].keepCalculating=0;
    sleep(10);

    return 0;
}