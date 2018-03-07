#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<cstdlib>
#include<ctime>
using namespace std;

void Swap(int &a,int &b)
{
    int tmp;
    tmp=a;
    a=b;
    b=tmp;
}

void inSort(int n,int a[])
{
    for(int i=1;i<n;i++)
    {
        for(int j=i;a[j]<a[j-1];j--)
            Swap(a[j],a[j-1]);
        for(int k=0;k<n;k++) cout<<a[k]<<" ";
        cout<<endl;
    }
}

int main()
{

    //int  a[]={-1,9,5,6,7};
    //inSort(5,a);
    if(1)
return 1;

    return 0;
}
