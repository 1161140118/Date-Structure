#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <string.h>
#define M 8
#define N 8

using namespace std;

//当前点
struct POINTER
{
    int pi;//第i行
    int pj;//第j列
};
//迷宫
struct MAZE
{
    int Graph[M][N];//矩阵图
    //int Path[M][N];//路径图
    POINTER Pre[M][N];//i,j的前导
};

//从文件读入图
void FInput(MAZE &G)
{
    FILE *fp;
    if( (fp=fopen("DS_Maze.txt","r"))==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    int *p=&G.Graph[0][0];
    for(int i=0;i<M*N;i++)
        fscanf(fp,"%d",p++);
}
//显示图信息
void show(MAZE G)
{
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
            cout<<G.Graph[i][j]<<" ";
        cout<<endl;
    }
}
//判断是否可到达，可到点入队,从点（1，1）开始遍历
void Reachable(POINTER P,MAZE &G,queue <POINTER> &Q)
{
    POINTER tmp;
    for(int i=-1;i<2;i++)
        for(int j=-1;j<2;j++)
        {
            tmp.pi=P.pi+i;
            tmp.pj=P.pj+j;
            if(G.Graph[tmp.pi][tmp.pj]==0)
            {
                G.Graph[tmp.pi][tmp.pj]=2;//走过标记2
                Q.push(tmp);//入队该点
                G.Pre[tmp.pi][tmp.pj]=P;
            }
        }
}

//广度优先搜索
void BFS(MAZE &G,queue <POINTER> &Q)
{
    POINTER head,out,P;
    P.pi=1;P.pj=1;
    out.pi=M-1;out.pj=N-1;
    head.pi=0;head.pj=0;
    if(G.Graph[P.pi][P.pj]!=0)
    {
        cout<<"迷宫非法！"<<endl;
        exit(0);
    }
    G.Pre[P.pi][P.pj]=head;//设置（1，1）的前导为（0，0）
    G.Graph[P.pi][P.pj]=2;//标志走过
    G.Graph[0][0]=2;//标志走过
    while(!((P.pi==out.pi)&&(P.pj==out.pj)) )
    {//队列非空且未至终点
        Reachable(P,G,Q);
        if(Q.empty())
        {
            cout<<"无出口！"<<endl;
            exit(0);
        }
        P=Q.front();
        Q.pop();
    }
}
//递归输出迷宫
void view(MAZE &G,int i,int j)
{
    if(i!=0||j!=0)
        view(G,G.Pre[i][j].pi,G.Pre[i][j].pj);
    cout<<"("<<i+1<<","<<j+1<<")"<<endl;
}

int main()
{
    MAZE G;
    queue <POINTER> Q;
    cout<<"迷宫如下：（目录下文本读入）"<<endl;
    FInput(G);
    show(G);
    BFS(G,Q);
    cout<<"最优路径为："<<endl;
    view(G,M-1,N-1);
    return 0;
}
