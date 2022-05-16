#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/resource.h>


struct customTimer{
    long real;
    double user;
    double system;
};

struct externalProgramParams{
    char* filePath;
    char** opts;
    int numberOfOpts;
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
    params.filePath = argv[startOptIndex];
    params.opts = malloc(sizeof(char*)*25);

    while(argv[i])
    {
        params.opts[j] = argv[i];
        i++;
        j++;
    }
    params.numberOfOpts = j;

    return params;
}

char* buildCommand(struct externalProgramParams programParams)
{
    static char command[100] = "";
    strcat(command, programParams.filePath);
    for(int i = 0; i<programParams.numberOfOpts; i++)
    {
        strcat(command, " ");
        strcat(command, programParams.opts[i]);
    }

    return command;
}

void runProgram(struct externalProgramParams programParams, int flagV, struct customTimer * timer)
{
    //char* command = buildCommand(programParams);
    //printf("Starting program with command: %s\n", command);

    if(flagV == 0)
    {
        int d = open("/dev/null", O_WRONLY);
        dup2(d,1);
    }
    char *env[]={NULL};
    //int result = system(command);

    pid_t pid;
    struct timespec requestStart, requestEnd;
    int wstatus;
    struct rusage* rusage = malloc(sizeof(struct rusage));

    if((pid = fork()) == -1)
        perror("fork error");
    else if (pid == 0)
    {
        execve(programParams.filePath, programParams.opts, NULL);
        printf("Return not expected.");
    }
    else
    {
        printf("\n pid: %d ppid: %d \n", getpid(), getppid());
        clock_gettime(CLOCK_REALTIME, &requestStart);
        wait4(pid, &wstatus, 0, rusage);
        clock_gettime(CLOCK_REALTIME, &requestEnd);
        timer->real += (requestEnd.tv_sec-requestStart.tv_sec) *1000000000 + (requestEnd.tv_nsec - requestStart.tv_nsec);
        
        printf("Real Time: %ld ns \n", timer->real);
        printf("System Time: %ld us \n", rusage->ru_stime.tv_sec*1000000 + rusage->ru_stime.tv_usec);
        printf("User Time: %ld us \n", rusage->ru_utime.tv_sec*1000000 + rusage->ru_utime.tv_usec);
        printf("End Of Program %s \n\n", programParams.filePath);
    }


}

int main(int argc, char **argv)
{
    int fv=0;
    long numOfRuns = 1;
    int opt, lastArgIndex;
    char *pathToFile;
    char **filesSwitches;
    struct customTimer timer;
    timer.real=0;
    timer.system=0;
    timer.user=0;

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

    struct externalProgramParams params = saveFilesPathAndSwitches(argc, lastArgIndex, argv);

    runProgram(params, fv, &timer);
    return 0;
}