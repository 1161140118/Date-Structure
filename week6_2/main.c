#include <stdio.h>
#include <stdlib.h>
#define N 100

int a[N]={0};
void input()
{
    int i;
    for(i=0;i<N;i++)
        scanf("%d",&a[i]);
}

int main()
{
    int temp=a[0],add=0;
    int i;
    input();
    for(i=0;i<N;i++)
    {
        if(a[i]>temp)
        {
            temp=a[i];
            add=i;
        }
    }
    printf("最大值为%d,为第%d个数。",temp,add+1);
    return 0;
}
