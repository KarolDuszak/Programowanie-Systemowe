#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    int fv=0, ft=0;
    int opt;
    while ((opt = getopt(argc, argv, "vt:")) != -1)
    {
        switch (opt)
        {
        case 'v':
            fv = 1;
            break;
        case 't':
            ft = 1;
            break;      
        }
    }
    return 0;
}