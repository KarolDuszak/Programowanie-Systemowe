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

    while(*(int*)flag==1)
    {
        sleep(1);
    }
    printf("KONIEC \n");
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

    for(int i=0; i<numberOfThreads;i++)
    {
        threads[i].keepCalculating=1;
        int status = pthread_create(&threads[i].thread, NULL, executeThread, &threads[i].keepCalculating);
        threads[i].lifetime = randomCalculationTime(maxLifeTime);
        printf("status: %d id: %ld life time: %d\n", status, threads[i].thread, threads[i].lifetime);
        sleep(1); //Za szybko sie tworza wiec zeby zroznicowac czasy umiescilem sleep bo wszystkie mialy taki sam czas
    }


    // Teraz to musi by wywolywane przez sygnal
    // trzeba mu przekazac jakos ta strukture
    // przy tworzeniu zeby set alarm a jak alarm sie odpali to zabic ten proces
    // mozna przekazac id np lub wskaznik i wtedy go zabic
    
    // moze trzymac ilosc aktywynych watkow zeby program zakonczyc dopiero jak
    // wszystkie zostana ubite?
    sleep(5);
    threads[0].keepCalculating=0;
    sleep(10);

    return 0;
}