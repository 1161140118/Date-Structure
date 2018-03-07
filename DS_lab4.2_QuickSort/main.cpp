#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#define RADIX_10 10
using namespace std;

int *A,*B;
    //int A[]={5,3,4,8,1,2};
int n;
int opt;//优化选项
int *Out;

//插入排序
inline void insertSort(int A[], int low,int high)
{
    int i, j, key;
    for (i = low; i <= high; i++)
    {
        key = A[i];
        for (j = i - 1; j >= low; j--)
        {
            if (A[j] > key)
            {
                A[j + 1] = A[j];
            }
            else
                break;
        }
        A[j + 1] = key;
    }
}

int Partition(int A[],int low,int high)
{
    if(opt>=1)
    {
        int r=( rand()%(high-low) + low );//随机坐标作为主元
        swap(A[r],A[high]);
    }
    int x=A[high];//最后一个数作主元
    int i=low-1;
    for(int j=low;j<high;j++)
    {
        if(A[j]<x)
        {
            i++;
            swap(A[i],A[j]);
        }
    }
    //经历上面的循环之后下标为从low到i（包括i）的数就均为小于x的数了，现在将主元和i+1位置上面的数进行交换
    A[high] = A[i + 1];
    A[i + 1] = x;
    return i + 1;
}

void QuickSort(int A[],int low,int high)
{
    if(low<high)
    {
        if(high-low<16&&n==2)//小于16时，用直接插入
        {
            insertSort(A,low,high);
        }
        else
        {
            int k= Partition(A,low,high);
            QuickSort(A,low,k-1);
            QuickSort(A,k+1,high);
        }
    }
}



int main()
{
    srand(time(NULL));
    clock_t clockBegin,clockEnd;

    /*cout<<"优化方式："<<endl;
    cin>>opt;*/
    int i,s,m;
    s=10;

    n=1e5;
    m=1e4;
    A=new int[n];
    B=new int[n];

    Out=new int[n];

    for(int j=0;j<5;j++)
    {
        for(i=0;i<n;i++)    A[i]=rand()%m+i;
        for(i=0;i<n;i++)    B[i]=A[i];
        cout<<endl;

        /** 优化快排 */
        opt=2;
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        clockBegin=clock();
        QuickSort(A,0,n-1);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        printf("优化快排用时 %ld 毫秒\n",clockEnd-clockBegin);

        /** 普通快排 */
        //for(i=0;i<s;i++) cout<<B[i]<<" ";
        //putchar('\n');
        opt=0;
        clockBegin=clock();
        //insertSort(B,0,n-1);
        QuickSort(B,0,n-1);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<B[i]<<" ";
        //putchar('\n');
        printf("普通快排用时 %ld 毫秒\n",clockEnd-clockBegin);

    }

    delete [] A;
    delete [] B;

    return 0;
}
