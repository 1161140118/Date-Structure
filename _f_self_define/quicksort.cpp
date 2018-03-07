#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

int *A,*B,*C;
    //int A[]={5,3,4,8,1,2};
int n;
int opt;//优化选项
int *Out;


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

//计数排序
void Counting_sort(int A[],int length_A,int k)
{//A为待排序数组，k为待排序元素的最大值
    int Cnt[k+1] = {0};//临时数组,数组长度为待排序元素最大值与最小值之差加1

    int i,j;
    for (j=0;j<length_A;j++)
    {//统计相同数值元素的个数
        Cnt[ A[j] ]++;
    }
    for (i=1;i<=k;i++)
    {//统计小于等于元素i的个数
        Cnt[ i ] += Cnt[i-1];
    }
    for (j=length_A-1;j>=0;j--)
    {
        Out[ Cnt[ A[j] ] -1] = A[j];
        Cnt[ A[j] ]--;
    }
}
//基数排序
void Radix_sort(int arr[],int number_of_data,int len)
{/* number_of_data是待排序元素的位数 */
    int counter = 0;
    int n =1;
    int i,j;
    while (counter<number_of_data)
    {
        int counter_for_index[10] = {0};//桶中的计数器 表示放了多少个元素
        int tmp[10][10] = {{0}};
        //将数据放入对应的桶中
        for (i = 0;i<len;i++)
        {
            int index = (arr[i]/n)%10;/* 计算待排序元素的最低位 */
            tmp[index][counter_for_index[index]++] = arr[i];
        }
        n*=10;
        counter++;//位数计数器
        //将放入桶中的数据写入原数组
        int k = 0;
        for (i= 0;i<10;i++)
        {
            for (j = 0;j<counter_for_index[i];j++)
            {
                arr[k++] = tmp[i][j];
            }
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
    C=new int[n];
    Out=new int[n];

    for(int j=0;j<5;j++)
    {
        for(i=0;i<n;i++)    A[i]=rand()%m+i;
        for(i=0;i<n;i++)    B[i]=A[i];
        for(i=0;i<n;i++)    C[i]=A[i];
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


        /** 计数排序 */
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        /*clockBegin=clock();
        Counting_sort(C,n,m);
        //Radix_sort(C,5,n);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        printf("计数排序用时 %ld 毫秒\n",clockEnd-clockBegin);*/
    }

    delete [] A;
    delete [] B;
    return 0;
}
