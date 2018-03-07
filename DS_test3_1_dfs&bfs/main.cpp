#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include "dfqueue.h"
#define N 10

using namespace std;

struct MTGraph
{
    int verlist[N];//顶点表
    int edge[N][N];//边表
    int n,e;//顶点数，边数
};

//从文件读入图
void Input(MTGraph &G)
{
    FILE *fp;
    if( (fp=fopen("F:\\DS_FILE\\DS_test3_1.txt","r"))==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    for(int i=0;i<N;i++)
        fscanf(fp,"%d",&G.verlist[i]);
    int sum_e=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            fscanf(fp,"%d",&G.edge[i][j]);
            if(G.edge[i][j]!=0)
                sum_e++;
        }
    }
    G.n=N;
    G.e=sum_e;

    cout<<"邻接矩阵如下:"<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            cout<<G.edge[i][j]<<' ';
        cout<<endl;
    }
    cout<<endl;
}

/*******************
    深度优先遍历
********************/
bool visited[N];
int dfn[N];
//从一个顶点出发，进行搜索
//递归算法
void DFS_re(MTGraph G,int i)
{
    int j;
    static int cnt=1;//编号
    cout<<G.verlist[i]<<' ';//visit i
    visited[i]=true;
    dfn[i]=cnt;//对 vi 编号
    cnt++;
    for(j=0;j<G.n;j++)
        if( (G.edge[i][j]==1)&& !visited[j] )
            DFS_re(G,j);
}
//非递归算法 栈操作
void DFS_inre(MTGraph G,int k)
{
    stack <int> S;
    int i,j;
    S.push(k);
    visited[k]=true;
    cout<<G.verlist[k]<<' ';

    S.push(k);//为循环储备
    while(!S.empty())
    {//栈非空时进行搜索
        i=S.top();
        S.pop();
        for(j=0;j<G.n;j++)
        {//搜索vi的临接点vj
            if( G.edge[i][j]==1 && !visited[j] )
            {//若vj未访问过
                cout<<G.verlist[j]<<' ';
                visited[j]=true;//访问过vj
                S.push(j);
                i=j;//深度
            }
        }//for
    }//while
}
//主算法
void DFSTraverse(MTGraph G)
{
    cout<<"DFS(recursion):"<<endl;
    int i;
    for(i=0;i<G.n;i++)
        visited[i]=false;
    for(i=0;i<G.n;i++)
        if(!visited[i])
            DFS_re(G,i);//从顶点i出发，进行搜索
    cout<<endl;

    cout<<"DFS(inrecursion):"<<endl;
    for(i=0;i<G.n;i++)
        visited[i]=false;
    for(i=0;i<G.n;i++)
        if(!visited[i])
            DFS_inre(G,i);//从顶点i出发，进行搜索
    cout<<endl;
}




/*******************
    广度优先遍历
********************/
//以vk为出发点，进行先广搜索
void BFS2(MTGraph G,int k)
{
    int i,j;//当前顶点与其邻接顶点
    Que Q;
    MakeNull(Q);

    cout<<G.verlist[k]<<' ';
    visited[k]=true;
    EnQueue(k,Q);

    while(!Empty(Q))
    {//队空时搜索结束
        i=DeQueue(Q);//vi出队
        for(j=0;j<G.n;j++)
        {//搜索vi的临接点vj
            if( G.edge[i][j]==1 && !visited[j] )
            {//若vj未访问过
                cout<<G.verlist[j]<<' ';
                visited[j]=true;//访问过vj
                EnQueue(j,Q);//访问过入队
            }
        }//for 检查vi的所有邻接顶点
    }//while 判断队列是否为空
}
//主算法
void BFSTraverse(MTGraph G)
{
    cout<<"BFS:"<<endl;
    int i;
    for(i=0;i<G.n;i++)
        visited[i]=false;
    for(i=0;i<G.n;i++)//非连同时循环有意义
        if(!visited[i])
            BFS2(G,i);//从顶点i出发，进行搜索
    cout<<endl;
}


int main()
{
    MTGraph G;
    Input(G);

    DFSTraverse(G);
    BFSTraverse(G);

    return 0;
}
