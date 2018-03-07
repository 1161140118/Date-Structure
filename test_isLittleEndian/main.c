#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isLittleEndian()
{
    int x=0x1;
    char *px=NULL;
    px=(char *)&x;
    return *px;
}

int main()
{
    printf("%x",isLittleEndian());
    return 0;
}
