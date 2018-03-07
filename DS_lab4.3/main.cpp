#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#define RADIX_10 10
using namespace std;

int *A,*B,*C;
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
/*****************************************
                计数排序
/*****************************************/
//计数排序
void countSort(int array[], int size ,int RANDMAX)
{

    //计数数组，用于统计数组array中各个不同数出现的次数
    //由于数组array中的数属于0...RANDMAX-1之间，所以countArray的大小要够容纳RANDMAX个int型的值
    int *countArray = (int *) calloc(RANDMAX, sizeof(int));
    //用于存放已经有序的数列
    int *sortedArray = (int *) calloc(size, sizeof(int));

    //统计数组array中各个不同数出现的次数，循环结束后countArray[i]表示数值i在array中出现的次数
    int index = 0;
    for (index = 0; index < size; ++index) {
        countArray[array[index]]++;
    }

    //统计数值比index小的数的个数，循环结束之后countArray[i]表示array中小于等于数值i的元素个数
    for (index = 1; index < RANDMAX; ++index) {
        countArray[index] += countArray[index - 1];
    }

    for (index = size - 1; index >= 0; --index) {
        //因为数组的起始下标为0，所以要减一
        sortedArray[countArray[array[index]] - 1] = array[index];
        //这里减一是为了保证当有多个值为array[index]的元素时，后出现的值为array[index]的元素
        //放在后面，也就是为了保证排序的稳定性
        --countArray[array[index]];
    }

    memcpy(array, sortedArray, size * sizeof(int));
    free(sortedArray);
    free(countArray);
}
/*****************************************
                 桶排序
/*****************************************/
//桶排序
void BucketSort(int a[],int b[],int n)
{
    int **bucket = new int*[10];
    for( int i = 0; i < 10; i++)
    {
        bucket[i] = new int[n];
    }
    int len[10];//各个桶的数据量
    for (int i = 0; i < 10; i++)//初始化
        len[i] = 0;
    for (int i = 0; i < n; i++)//将数据输入后分桶存入
    {
        bucket[a[i]/100000][len[a[i]/100000]] = a[i];
        len[(a[i]/100000)]++;
    }
    for (int i = 0; i < 10; i++)//每个桶内快排
    {
        QuickSort( bucket[i] , 0 , len[i]-1);
    }
    int count = 0;
    for (int i = 0; i < 10; i++)//将桶的值赋给b
    {
        for (int j = 0; j < len[i]; j++)
        {
            b[count++] = bucket[i][j];
        }
    }
    for (int i = 0; i < 10; i++)
    {
        delete [] bucket[i];
    }
    delete bucket;
}

/*****************************************
                基数排序
/*****************************************/
//基数排序：获取指定位数字
int GetNumInPos(int num,int pos)
{
    int temp = 1;
    for (int i = 0; i < pos - 1; i++)
        temp *= 10;

    return (num / temp) % 10;
}
//基数排序
void RadixSort(int* pDataArray,int KEYNUM, int iDataNum)
{//待排序数组，数据最大位数，数据个数
    int *radixArrays[RADIX_10];    //分别为0~9的序列空间
    for (int i = 0; i < 10; i++)
    {
        radixArrays[i] = (int *)malloc(sizeof(int) * (iDataNum + 1));
        radixArrays[i][0] = 0;    //index为0处记录这组数据的个数
    }

    for (int pos = 1; pos <= KEYNUM; pos++)    //从个位开始到31位
    {
        for (int i = 0; i < iDataNum; i++)    //分配过程
        {
            int num = GetNumInPos(pDataArray[i], pos);
            int index = ++radixArrays[num][0];
            radixArrays[num][index] = pDataArray[i];
        }

        for (int i = 0, j =0; i < RADIX_10; i++)    //收集
        {
            for (int k = 1; k <= radixArrays[i][0]; k++)
                pDataArray[j++] = radixArrays[i][k];
            radixArrays[i][0] = 0;    //复位
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
    opt=2;
    for(int j=0;j<5;j++)
    {
        for(i=0;i<n;i++)    A[i]=rand()%m;
        for(i=0;i<n;i++)    B[i]=A[i];
        for(i=0;i<n;i++)    C[i]=A[i];
        cout<<endl;

        /** 计数排序 */
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        clockBegin=clock();
        countSort(A,n,m+n);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        printf("计数排序用时 %ld 毫秒\n",clockEnd-clockBegin);

        /** 桶排序  */
        //for(i=0;i<s;i++) cout<<B[i]<<" ";
        //putchar('\n');
        clockBegin=clock();
        BucketSort(B,Out,n);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<B[i]<<" ";
        //putchar('\n');
        printf("桶排序 用时 %ld 毫秒\n",clockEnd-clockBegin);


        /** 基数排序 */
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        clockBegin=clock();
        RadixSort(C,5,n);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        printf("基数排序用时 %ld 毫秒\n",clockEnd-clockBegin);
    }

    delete [] A;
    delete [] B;
    delete [] C;
    delete [] Out;
    return 0;
}
