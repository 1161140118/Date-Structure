#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int new_strcmp(char a[],char b[])
{
    char na[5],nb[5];
    int i;
    strcpy(na,a);
    strcpy(nb,b);

    for(i=0;i<4;i++)
    {
        if(na[i]<=57)
            na[i]=na[i]+49;
        if(nb[i]<=57)
            nb[i]=nb[i]+49;
    }
    return strcmp(na,nb);
}

void range(char a[][5])
{
    int i,j;
    char temp[5];
    strcpy(temp,a[0]);
    for(i=0;i<7;i++)
    {
        for(j=i+1;j<8;j++)
        {
            if( (new_strcmp(a[j],a[i])) <0)
                {
                    strcpy(temp,a[i]);
                    strcpy(a[i],a[j]);
                    strcpy(a[j],temp);
                }
        }
    }

}

int main()
{
    char a[8][5]={"PAB","5C","PABC","CXY","CRSI","7","B899","B9"};
    int i;
    range(a);
    for(i=0;i<8;i++)
    {
        puts(a[i]);
    }
    return 0;
}
