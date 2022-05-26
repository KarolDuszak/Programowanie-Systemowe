// PS IN1 320 LAB06
// Karol Duszak
// dk44312@zut.edu.pl

#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

static pthread_key_t startTimerKey;
static pthread_once_t startTimerOnce = PTHREAD_ONCE_INIT;
static int * timerStart;

static void freeMemory(void *buffer)
{
    free(buffer);
}

static void createKey(void)
{
    pthread_key_create(&startTimerKey, freeMemory);
}

void startTimer()
{
    struct timespec timestamp;
    clock_gettime(CLOCK_REALTIME, &timestamp);
    
    pthread_once(&startTimerOnce, createKey);
    timerStart = pthread_getspecific(startTimerKey);
    if(timerStart == NULL)
    {
        timerStart= malloc(sizeof(int));
        *timerStart = (int)timestamp.tv_sec*1000 + (int)timestamp.tv_nsec/1000000;
        pthread_setspecific(startTimerKey, timerStart);
    }
}

int stopTimer()
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    int timeEnd = (int)time.tv_sec*1000 + (int)time.tv_nsec/1000000;
    
    int* start;
    start = pthread_getspecific(startTimerKey);
    return timeEnd - *start;
}