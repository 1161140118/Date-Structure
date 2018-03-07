#include <iostream>
#define MAX 1000     //无穷
#define MIN -1      //极小
#define N 8         //顺串数
#define M 3         //每个顺串中的元素树数

using namespace std;

/**********************************************
1.用数组，严格注意边界问题
2.用算法修改代码，而不是用代码去处理“特殊情况”
**********************************************/

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
    int R[N][M]={10,15,16,
                 9,20,38,
                 20,20,30,
                 6,15,25,
                 8,15,20,
                 9,11,16,
                 90,100,110,
                 17,18,20};

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
