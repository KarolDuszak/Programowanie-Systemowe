#include <stdlib.h>
#include <string.h>

int main(){
    unsigned char *p1 = malloc(10*sizeof(unsigned char));
    unsigned char *p2 = malloc(20*sizeof(unsigned char));
    memset(p1, 1, 10);
    p1[10]=2;
    return 0;
}