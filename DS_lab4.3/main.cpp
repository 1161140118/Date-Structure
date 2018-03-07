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
int opt;//�Ż�ѡ��
int *Out;

//��������
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
        int r=( rand()%(high-low) + low );//���������Ϊ��Ԫ
        swap(A[r],A[high]);
    }
    int x=A[high];//���һ��������Ԫ
    int i=low-1;
    for(int j=low;j<high;j++)
    {
        if(A[j]<x)
        {
            i++;
            swap(A[i],A[j]);
        }
    }
    //���������ѭ��֮���±�Ϊ��low��i������i�������;�ΪС��x�����ˣ����ڽ���Ԫ��i+1λ������������н���
    A[high] = A[i + 1];
    A[i + 1] = x;
    return i + 1;
}

void QuickSort(int A[],int low,int high)
{
    if(low<high)
    {
        if(high-low<16&&n==2)//С��16ʱ����ֱ�Ӳ���
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
                ��������
/*****************************************/
//��������
void countSort(int array[], int size ,int RANDMAX)
{

    //�������飬����ͳ������array�и�����ͬ�����ֵĴ���
    //��������array�е�������0...RANDMAX-1֮�䣬����countArray�Ĵ�СҪ������RANDMAX��int�͵�ֵ
    int *countArray = (int *) calloc(RANDMAX, sizeof(int));
    //���ڴ���Ѿ����������
    int *sortedArray = (int *) calloc(size, sizeof(int));

    //ͳ������array�и�����ͬ�����ֵĴ�����ѭ��������countArray[i]��ʾ��ֵi��array�г��ֵĴ���
    int index = 0;
    for (index = 0; index < size; ++index) {
        countArray[array[index]]++;
    }

    //ͳ����ֵ��indexС�����ĸ�����ѭ������֮��countArray[i]��ʾarray��С�ڵ�����ֵi��Ԫ�ظ���
    for (index = 1; index < RANDMAX; ++index) {
        countArray[index] += countArray[index - 1];
    }

    for (index = size - 1; index >= 0; --index) {
        //��Ϊ�������ʼ�±�Ϊ0������Ҫ��һ
        sortedArray[countArray[array[index]] - 1] = array[index];
        //�����һ��Ϊ�˱�֤���ж��ֵΪarray[index]��Ԫ��ʱ������ֵ�ֵΪarray[index]��Ԫ��
        //���ں��棬Ҳ����Ϊ�˱�֤������ȶ���
        --countArray[array[index]];
    }

    memcpy(array, sortedArray, size * sizeof(int));
    free(sortedArray);
    free(countArray);
}
/*****************************************
                 Ͱ����
/*****************************************/
//Ͱ����
void BucketSort(int a[],int b[],int n)
{
    int **bucket = new int*[10];
    for( int i = 0; i < 10; i++)
    {
        bucket[i] = new int[n];
    }
    int len[10];//����Ͱ��������
    for (int i = 0; i < 10; i++)//��ʼ��
        len[i] = 0;
    for (int i = 0; i < n; i++)//������������Ͱ����
    {
        bucket[a[i]/100000][len[a[i]/100000]] = a[i];
        len[(a[i]/100000)]++;
    }
    for (int i = 0; i < 10; i++)//ÿ��Ͱ�ڿ���
    {
        QuickSort( bucket[i] , 0 , len[i]-1);
    }
    int count = 0;
    for (int i = 0; i < 10; i++)//��Ͱ��ֵ����b
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
                ��������
/*****************************************/
//�������򣺻�ȡָ��λ����
int GetNumInPos(int num,int pos)
{
    int temp = 1;
    for (int i = 0; i < pos - 1; i++)
        temp *= 10;

    return (num / temp) % 10;
}
//��������
void RadixSort(int* pDataArray,int KEYNUM, int iDataNum)
{//���������飬�������λ�������ݸ���
    int *radixArrays[RADIX_10];    //�ֱ�Ϊ0~9�����пռ�
    for (int i = 0; i < 10; i++)
    {
        radixArrays[i] = (int *)malloc(sizeof(int) * (iDataNum + 1));
        radixArrays[i][0] = 0;    //indexΪ0����¼�������ݵĸ���
    }

    for (int pos = 1; pos <= KEYNUM; pos++)    //�Ӹ�λ��ʼ��31λ
    {
        for (int i = 0; i < iDataNum; i++)    //�������
        {
            int num = GetNumInPos(pDataArray[i], pos);
            int index = ++radixArrays[num][0];
            radixArrays[num][index] = pDataArray[i];
        }

        for (int i = 0, j =0; i < RADIX_10; i++)    //�ռ�
        {
            for (int k = 1; k <= radixArrays[i][0]; k++)
                pDataArray[j++] = radixArrays[i][k];
            radixArrays[i][0] = 0;    //��λ
        }
    }
}

int main()
{
    srand(time(NULL));
    clock_t clockBegin,clockEnd;

    /*cout<<"�Ż���ʽ��"<<endl;
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

        /** �������� */
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        clockBegin=clock();
        countSort(A,n,m+n);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        printf("����������ʱ %ld ����\n",clockEnd-clockBegin);

        /** Ͱ����  */
        //for(i=0;i<s;i++) cout<<B[i]<<" ";
        //putchar('\n');
        clockBegin=clock();
        BucketSort(B,Out,n);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<B[i]<<" ";
        //putchar('\n');
        printf("Ͱ���� ��ʱ %ld ����\n",clockEnd-clockBegin);


        /** �������� */
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        clockBegin=clock();
        RadixSort(C,5,n);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        printf("����������ʱ %ld ����\n",clockEnd-clockBegin);
    }

    delete [] A;
    delete [] B;
    delete [] C;
    delete [] Out;
    return 0;
}
