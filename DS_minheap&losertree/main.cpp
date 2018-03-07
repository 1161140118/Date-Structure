#include <iostream>
#include <algorithm>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10000  //��������
#define MAX 100000     //����
#define MIN -1      //��С
#define N 8         //˳����
#define M 1280        //ÿ��˳���е�Ԫ����
using namespace std;

int A[MaxSize]; //����������


/************************
        MIN HEAP
*************************/

struct HEAP
{
    int pro[MaxSize];
    int n;      //����������
};

//����һ���ն�
void MaxHeap(HEAP &heap)
{
    heap.n=0;
}
//�ж϶��Ƿ�Ϊ��
bool HeapEmpty(HEAP heap)
{
    return (!heap.n);
}
//�ж϶��Ƿ�Ϊ��
bool HeapFull(HEAP heap)
{
    return (heap.n==MaxSize-1);
}
//����һ��Ԫ��
void Insert(HEAP &heap,int p)
{
    int i=0;
    if(!HeapFull(heap))     //�Ѳ���
    {
        heap.n++;
        i=heap.n;
        while((i!=1)&&(p>heap.pro[i/2]))    //[i/2]Ϊi�ĸ��ڵ�
        {
            heap.pro[i]=heap.pro[i/2];
            i=i/2;
        }
        heap.pro[i]=p;
    }
    else
        cout<<"����ʧ�ܣ���������"<<endl;
}
//ɾ���Ѷ�Ԫ��
int DeleteMax(HEAP &heap)
{
    int parent=1,child=2;
    int p,tmp;
    if(!HeapEmpty(heap))
    {
        p=heap.pro[1];
        tmp=heap.pro[heap.n--]; //�����ĩԪ��
        while(child<=heap.n)
        {/*�ӶѶ���ʼ����Ԫ��������ϴ�*/
            if( (child<heap.n)&&(heap.pro[child]<heap.pro[child+1]) )   //�ϴ�����
                child++;
            if(tmp>heap.pro[child])    //����ĩԪ�ؽϴ� ����ڵ�λ��
                break;
            heap.pro[parent]=heap.pro[child];
            parent=child;   //ѡ���֧
            child*=2;       //ɨ����һ��
        }//while
        heap.pro[parent]=tmp;   //�ö�ĩԪ�����ȱ
        return p;
    }//if
    return heap.pro[0];
}

//��������
void Input(HEAP &heap)
{
    for(int i=0;i<MaxSize-1;i++)
    {//����
        Insert(heap,A[i]);
    }
    cout<<"������ɣ�"<<endl;
    putchar('\n');
}

//�������
void Output(HEAP &heap)
{
    int n=heap.n;
    int *tmp=NULL;
    tmp=new int[n];
    int i;
    for(i=0;i<n;i++)
    {
        tmp[i]=DeleteMax(heap);
    }

}

/**************************
        LOSER TREE
***************************/
typedef struct
{
    int val;  //��ǰ��˳�����������ֵ
    int p;  //˳���е�i����
}KEY;

//������
int CreatLoseTree(int ls[],KEY k[])
{
    int tmp;
    int flag=0;   //��������
    for (int i=0;i<N;i++)
    {//����˳����������
        flag=0;
        int order=i;//��order��˳��
        int parent=order+N-2;// parent/2 Ϊ˳�����ڵ�
        while (!flag)   //����Ϊls[N-1]
        {
            if(parent!=0)//δ����������
            {
                parent/=2;
                if (k[order].val>=k[ls[parent]].val) //��order���븸�ڵ���߱Ƚ� orderΪ����
                {
                    tmp=ls[parent];
                    ls[parent]=order;
                    order=tmp;  //orderΪʤ��
                }
            }
            else
            {
                parent=N-1;flag=1;//��־��������
                if (k[order].val<=k[ls[parent]].val||k[ls[parent]].val==MIN)
                {
                    tmp=ls[parent];
                    ls[parent]=order;
                    order=tmp;
                }
            }
        }//while
    }
    return ls[N-1];
}
//���ð�������˳������Ԫ������orderΪ�ϴ������˳����
int RunLoseTree(int ls[],KEY k[],int order,int R[N][M])
{
    cout<<k[order].val<<endl;  //�������ֵ

    if(k[order].p!=M-1)   //δȡ�����һ��ֵ
        k[order].val=R[order][++k[order].p];    //��order˳��ȡ��ֵ
    else
        k[order].val=MAX;   //��Ϊ���ֵ

    int tmp;
    //�Ե�order������
    int parent=order+N-1; // parent/2 Ϊ˳�����ڵ�
    int flag=0;
    while (!flag)   //����Ϊls[N-1]
    {
        if(parent!=0)//δ����������
        {
            parent/=2;
            if (k[order].val>=k[ls[parent]].val) //��order���븸�ڵ���߱Ƚ� orderΪ����
            {
                tmp=ls[parent];
                ls[parent]=order;
                order=tmp;  //orderΪʤ��
            }
        }
        else
        {
            parent=N-1;flag=1;//��־��������
            if (k[order].val<=k[ls[parent]].val||k[ls[parent]].val==MIN)
            {
                tmp=ls[parent];
                ls[parent]=order;
                order=tmp;
            }
        }
    }//while
    return ls[N-1];
}


int main()
{
    srand(time(NULL));
    clock_t clockBegin,clockEnd;
    for(int i=0;i<MaxSize;i++) A[i]=rand()%10000 ;// ���������

    //��С������
    HEAP heap;
    MaxHeap(heap);

    clockBegin=clock();
    Input(heap);
    Output(heap);
    clockEnd=clock();
    printf("С����������ʱ %ld ����\n",clockEnd-clockBegin);

    //����������
    int R[N][M];
    for(int i=0;i<N-1;i++)
    {
        for(int j=0;j<M;j++)
        {
            R[i][j]=A[i*M+j];
        }
    }
    for(int j=0;j<M;j++)
    {
        if()
    }

    KEY k[N+1];
    int ls[N];
    for (int i=0;i<N;i++) ls[i]=N;    //��ʼ�����а������ ls[N-1]Ϊ����
    for (int i=0;i<N;i++)
    {
        k[i].val=R[i][0]; //��ʼ����˳�����������Ԫ��
        k[i].p=0;
    }
    k[N].val=MIN;
    k[N].p=0;        //��ʼ����������

    int order;
    order=CreatLoseTree(ls,k);
    cout<<"Ԫ������:"<<endl;
    for(int i=0;i<M*N;i++)
    {
        order=RunLoseTree(ls,k,order,R);
    }


    return 0;
}
