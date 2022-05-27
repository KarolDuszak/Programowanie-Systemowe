// PS IN1 320 LAB07
// Karol Duszak
// dk44312@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
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

char* loadDict(char* path)
{
    
}

int main(int argc, char **argv)
{
    char* hash=NULL;
    char* pathToFile=NULL;
    int threadsNumber = 0;
    int opt;
    long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);

    while ((opt = getopt(argc, argv, "h:p:t:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            hash = optarg;
            break;
        case 'p':
            pathToFile = optarg;
            break;
        case 't':
                if(isNumber(optarg)==0)
                {
                    printf("Passed value for switch t is not a number: %s closing program\n", optarg);
                    exit(1);
                }
                char* cvalue = optarg;
                threadsNumber = strtol(cvalue, NULL, 10);
                if(threadsNumber>number_of_processors)
                {
                    threadsNumber = number_of_processors;
                }
            break;
        }
    }

    printf("Hash: %s pahtToFile: %s threads: %d MaxNrOfProcesors: %ld\n", hash, pathToFile, threadsNumber, number_of_processors);
    return 0;

}