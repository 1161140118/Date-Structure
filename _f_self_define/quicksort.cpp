#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

int *A,*B,*C;
    //int A[]={5,3,4,8,1,2};
int n;
int opt;//�Ż�ѡ��
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

//��������
void Counting_sort(int A[],int length_A,int k)
{//AΪ���������飬kΪ������Ԫ�ص����ֵ
    int Cnt[k+1] = {0};//��ʱ����,���鳤��Ϊ������Ԫ�����ֵ����Сֵ֮���1

    int i,j;
    for (j=0;j<length_A;j++)
    {//ͳ����ͬ��ֵԪ�صĸ���
        Cnt[ A[j] ]++;
    }
    for (i=1;i<=k;i++)
    {//ͳ��С�ڵ���Ԫ��i�ĸ���
        Cnt[ i ] += Cnt[i-1];
    }
    for (j=length_A-1;j>=0;j--)
    {
        Out[ Cnt[ A[j] ] -1] = A[j];
        Cnt[ A[j] ]--;
    }
}
//��������
void Radix_sort(int arr[],int number_of_data,int len)
{/* number_of_data�Ǵ�����Ԫ�ص�λ�� */
    int counter = 0;
    int n =1;
    int i,j;
    while (counter<number_of_data)
    {
        int counter_for_index[10] = {0};//Ͱ�еļ����� ��ʾ���˶��ٸ�Ԫ��
        int tmp[10][10] = {{0}};
        //�����ݷ����Ӧ��Ͱ��
        for (i = 0;i<len;i++)
        {
            int index = (arr[i]/n)%10;/* ���������Ԫ�ص����λ */
            tmp[index][counter_for_index[index]++] = arr[i];
        }
        n*=10;
        counter++;//λ��������
        //������Ͱ�е�����д��ԭ����
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

    for(int j=0;j<5;j++)
    {
        for(i=0;i<n;i++)    A[i]=rand()%m+i;
        for(i=0;i<n;i++)    B[i]=A[i];
        for(i=0;i<n;i++)    C[i]=A[i];
        cout<<endl;

        /** �Ż����� */
        opt=2;
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        clockBegin=clock();
        QuickSort(A,0,n-1);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        printf("�Ż�������ʱ %ld ����\n",clockEnd-clockBegin);

        /** ��ͨ���� */
        //for(i=0;i<s;i++) cout<<B[i]<<" ";
        //putchar('\n');
        opt=0;
        clockBegin=clock();
        //insertSort(B,0,n-1);
        QuickSort(B,0,n-1);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<B[i]<<" ";
        //putchar('\n');
        printf("��ͨ������ʱ %ld ����\n",clockEnd-clockBegin);


        /** �������� */
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        /*clockBegin=clock();
        Counting_sort(C,n,m);
        //Radix_sort(C,5,n);
        clockEnd=clock();
        //for(i=0;i<s;i++) cout<<A[i]<<" ";
        //putchar('\n');
        printf("����������ʱ %ld ����\n",clockEnd-clockBegin);*/
    }

    delete [] A;
    delete [] B;
    return 0;
}
