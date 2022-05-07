#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

struct customTimer{

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

void saveFilesPathAndSwitches(int *filePath, int *filesSwitches, int startIndex, char* args)
{

}

int main(int argc, char **argv)
{
    int fv=0;
    long numOfRuns = 1;
    int opt, lastArgIndex;
    char *pathToFile;
    char **filesSwitches;

    for(int i=0; i< argc ; i++)
    {
        printf("%s \n", argv[i]);
    }
    while ((opt = getopt(argc, argv, "+vt:")) != -1)
    {
        switch (opt)
        {
        case 'v':
            fv = 1;
            lastArgIndex = optind;
            break;
        case 't':
        //Konwersja na int ze stringa
            if(isNumber(optarg)==0)
            {
                printf("Passed value for switch t is not a number: %s closing program\n", optarg);
                exit(1);
            }
            char* tvalue = optarg;
            numOfRuns = strtol(tvalue, NULL, 10);
            lastArgIndex = optind;
            break;
        }
    }

    printf("Question Mark opt: %d\n", lastArgIndex);
    printf("index last opt: %s\n", argv[lastArgIndex]);


    printf("fV: %d, number of runs: %ld\n", fv, numOfRuns);
    return 0;
}