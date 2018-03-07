#include <iostream>
#include <algorithm>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10000  //数据总数
#define MAX 100000     //无穷
#define MIN -1      //极小
#define N 8         //顺串数
#define M 1280        //每个顺串中的元素数
using namespace std;

int A[MaxSize]; //待排序数组


/************************
        MIN HEAP
*************************/

struct HEAP
{
    int pro[MaxSize];
    int n;      //堆中数据数
};

//创建一个空堆
void MaxHeap(HEAP &heap)
{
    heap.n=0;
}
//判断堆是否为空
bool HeapEmpty(HEAP heap)
{
    return (!heap.n);
}
//判断堆是否为满
bool HeapFull(HEAP heap)
{
    return (heap.n==MaxSize-1);
}
//插入一个元素
void Insert(HEAP &heap,int p)
{
    int i=0;
    if(!HeapFull(heap))     //堆不满
    {
        heap.n++;
        i=heap.n;
        while((i!=1)&&(p>heap.pro[i/2]))    //[i/2]为i的父节点
        {
            heap.pro[i]=heap.pro[i/2];
            i=i/2;
        }
        heap.pro[i]=p;
    }
    else
        cout<<"插入失败，堆已满！"<<endl;
}
//删除堆顶元素
int DeleteMax(HEAP &heap)
{
    int parent=1,child=2;
    int p,tmp;
    if(!HeapEmpty(heap))
    {
        p=heap.pro[1];
        tmp=heap.pro[heap.n--]; //保存堆末元素
        while(child<=heap.n)
        {/*从堆顶开始，将元素逐层向上串*/
            if( (child<heap.n)&&(heap.pro[child]<heap.pro[child+1]) )   //较大子树
                child++;
            if(tmp>heap.pro[child])    //若堆末元素较大 则填补节点位置
                break;
            heap.pro[parent]=heap.pro[child];
            parent=child;   //选择分支
            child*=2;       //扫描下一层
        }//while
        heap.pro[parent]=tmp;   //用堆末元素填补空缺
        return p;
    }//if
    return heap.pro[0];
}

//读入数据
void Input(HEAP &heap)
{
    for(int i=0;i<MaxSize-1;i++)
    {//读入
        Insert(heap,A[i]);
    }
    cout<<"输入完成！"<<endl;
    putchar('\n');
}

//整理输出
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
    int val;  //当前该顺串参与排序的值
    int p;  //顺串中第i个数
}KEY;

//创建树
int CreatLoseTree(int ls[],KEY k[])
{
    int tmp;
    int flag=0;   //经历树顶
    for (int i=0;i<N;i++)
    {//遍历顺串，建立树
        flag=0;
        int order=i;//第order个顺串
        int parent=order+N-2;// parent/2 为顺串父节点
        while (!flag)   //树顶为ls[N-1]
        {
            if(parent!=0)//未到二叉树顶
            {
                parent/=2;
                if (k[order].val>=k[ls[parent]].val) //第order串与父节点败者比较 order为败者
                {
                    tmp=ls[parent];
                    ls[parent]=order;
                    order=tmp;  //order为胜者
                }
            }
            else
            {
                parent=N-1;flag=1;//标志经历树顶
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
//利用败者树对顺串所有元素排序，order为上次输出的顺串序
int RunLoseTree(int ls[],KEY k[],int order,int R[N][M])
{
    cout<<k[order].val<<endl;  //输出树顶值

    if(k[order].p!=M-1)   //未取到最后一个值
        k[order].val=R[order][++k[order].p];    //第order顺串取次值
    else
        k[order].val=MAX;   //置为最大值

    int tmp;
    //对第order串处理
    int parent=order+N-1; // parent/2 为顺串父节点
    int flag=0;
    while (!flag)   //树顶为ls[N-1]
    {
        if(parent!=0)//未到二叉树顶
        {
            parent/=2;
            if (k[order].val>=k[ls[parent]].val) //第order串与父节点败者比较 order为败者
            {
                tmp=ls[parent];
                ls[parent]=order;
                order=tmp;  //order为胜者
            }
        }
        else
        {
            parent=N-1;flag=1;//标志经历树顶
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
    for(int i=0;i<MaxSize;i++) A[i]=rand()%10000 ;// 生成随机数

    //最小堆排序
    HEAP heap;
    MaxHeap(heap);

    clockBegin=clock();
    Input(heap);
    Output(heap);
    clockEnd=clock();
    printf("小根堆排序用时 %ld 毫秒\n",clockEnd-clockBegin);

    //败者树排序
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
    for (int i=0;i<N;i++) ls[i]=N;    //初始化树中败者序号 ls[N-1]为树顶
    for (int i=0;i<N;i++)
    {
        k[i].val=R[i][0]; //初始化各顺串参与排序的元素
        k[i].p=0;
    }
    k[N].val=MIN;
    k[N].p=0;        //初始建树辅助串

    int order;
    order=CreatLoseTree(ls,k);
    cout<<"元素序列:"<<endl;
    for(int i=0;i<M*N;i++)
    {
        order=RunLoseTree(ls,k,order,R);
    }


    return 0;
}
