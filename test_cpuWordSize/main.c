#include <stdio.h>
#include <stdlib.h>

int cpuWordSize()
{
    unsigned long x=0xFFFFFFFF;
    if(x+1)
        return 64;
    else
        return 32;
}


int main()
{
    printf("cpuWorlSize:%d\n",cpuWordSize());
    return 0;
}
