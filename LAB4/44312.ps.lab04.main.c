#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

struct customTimer{

};

struct externalProgramParams{
    char* filePath;
    char** opts;
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

struct externalProgramParams saveFilesPathAndSwitches(int argc, int startOptIndex, char** argv)
{
    struct externalProgramParams params;
    int i = startOptIndex+1;
    int j = 0;
    char** options = malloc((argc - startOptIndex)*sizeof(char*));
    strcpy(params.filePath, argv[startOptIndex]);

    params.opts = malloc(sizeof(char*)*25);

    while(argv[i])
    {
        strcpy(params.opts[j],argv[i]);
        i++;
        j++;
    }
    return params;
}

int main(int argc, char **argv)
{
    int fv=0;
    long numOfRuns = 1;
    int opt, lastArgIndex;
    char *pathToFile;
    char **filesSwitches;

    //Printing order of argstemp implementation
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

    printf("Position of last opt: %d\n", lastArgIndex);
    printf("Value on index: %s\n", argv[lastArgIndex]);
    
    struct externalProgramParams params = saveFilesPathAndSwitches(argc, lastArgIndex, argv);
    printf("FilePath: %s, Opt1 %s, Opt2 %s\n", params.filePath, params.opts[0],params.opts[1]);
    printf("fV: %d, number of runs: %ld\n", fv, numOfRuns);
    return 0;
}