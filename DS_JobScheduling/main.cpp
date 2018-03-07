#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define N 8
//邻接矩阵
typedef struct node_Graph
{
    int time;//完成时间
    char name;//序号
}Graph[N+1][N+1];
int VE[N+1]={0};//最早开始时间
int VL[N+1]={0};//最晚结束时间
void FInput(Graph &G)
{
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        {
            G[i][j].name='-';
            G[i][j].time=-1;
        }
    FILE *fp;
    if( (fp=fopen("Schedul.txt","r"))==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    int i=0,j=0,t=0;
    char c;
    while(!(i==7&&j==8))
    {//未到最后一个工序，循环
        fscanf(fp,"%d",&i);
        fscanf(fp,"%d",&j);
        fscanf(fp," %c",&c);
        fscanf(fp,"%d",&t);
        G[i][j].name=c;
        G[i][j].time=t;
    }
}
//调试
void Show(Graph G)
{
    cout<<"邻接矩阵："<<endl;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++) cout<<G[i][j].name<<G[i][j].time<<"\t";
        cout<<endl;
    }
    cout<<"顶点表："<<endl;
    for(int i=1;i<=N;i++) cout<<VE[i]<<" "<<VL[i]<<endl;
}
//求关键路径
void AOE(Graph G)
{
    int i=0,j=0,tv;
    //VE
    for(i=1;i<N;i++)
        for(j=1;j<=N;j++)
            if(G[i][j].time>0)
            {
                tv=G[i][j].time+VE[i];
                if(tv>VE[j])   VE[j]=tv;
            }
    //VL
    for(i=1;i<=N;i++)   VL[i]=VE[N];//VL初始化为最长时间
    for(j=8;j>0;j--)
        for(i=1;i<N;i++)
            if(G[i][j].time>0)
            {
                tv=VL[j]-G[i][j].time;
                if(tv<VL[i])    VL[i]=tv;
            }
}
//根据AOE安排日程
void Schedul(Graph G)
{
    cout<<"工程至少在 "<<VE[N]<<" 天内完成。"<<endl<<endl;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(G[i][j].time>0)
                printf("第%2d-%2d天内完成工序%c.\n",VE[i]+1,VL[j]+1,G[i][j].name);
}
int main()
{
    Graph G;
    FInput(G);
    AOE(G);
    //Show(G);
    Schedul(G);
    return 0;
}
