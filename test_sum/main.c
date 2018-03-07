#include <stdio.h>
#include <stdlib.h>

int sum(int a[],unsigned len)
{
    int i,sum=0;
    //printf("len-1=%d\n",len-1);

    //for(i=0;i<=len-1;i++)
    //    sum += a[i];
    if(len-1<0)
    {
        printf("ÓÐ·ûºÅ");
    }
    else
    {
        printf("ÎÞ·ûºÅ");
    }
    return sum;
}

int main()
{
    int a[3]={1,2,3};
    unsigned int x=1;
    unsigned int y=2;
    //printf("%ud",x-y);
    //printf("%d",sum(a,0));
    printf("%ud",-1);
    return 0;
}
