#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

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
    long result=1;
    int value =1;

    while(1)
    {
        result = result * value;
        value++;
    }
    printf("Result: %ld", result);
}

int main(int argc, char** argv)
{
    //l <- subprocess life time
    //c <- subprocess creation time
    int timeToCreate=0, maxLifeTime=0;
    int opt;

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

    printf("Lifetime: %d Creation time: %d\n", maxLifeTime, timeToCreate);
    calculateFactorial();
    return 0;
}