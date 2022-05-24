#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <time.h>

struct timespec requestStart, requestEnd;

void startTimer()
{
    clock_gettime(CLOCK_REALTIME, &requestStart);
}

time_t stopTimer()
{
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    return requestEnd.tv_sec-requestStart.tv_sec;
}