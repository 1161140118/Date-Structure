#include <stdio.h>
#include <stdlib.h>

int max(a,b)
{
    if(a>b)
        return a;
    return b;
}

int f(int x)
{
    int s=0;
    printf("%d_",x);
    while(x++ >0) s+=f(x);
    return max(s,1);
}

int main()
{
    f(35);
    return 0;
}
