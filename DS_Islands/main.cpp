#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#define N 5    //顶点数
using namespace std;
/***********************************
    1.不允许使用没有命名的结构体？
    2.慎重对待数组下标运算
************************************/
//边
typedef struct node1
{
    int bgn;//头顶点
    int end;//尾顶点
    double weight;//权值
}Edge[N*(N-1)/2+1];
/** 注意！实际上为N(N-1)/2条边 */
int n_edge=N*(N-1)/2;

//顶点坐标
typedef struct node2
{
    int v;//顶点序号
    int x;//顶点横坐标
    int y;//顶点纵坐标
}Vertex[N];
bool Graph[N][N]={0};
void DataError(int a)
{
    if(a>1000||a<0)
    {
        cout<<"数据错误！（0<=x,y<=1000）"<<endl;
        exit(0);
    }
}
//文件读入坐标
void FInput(Vertex &ver)
{
    FILE *fp=NULL;
    if( (fp=fopen("Islands.txt","r"))==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    for(int i=0;i<N;i++)
    {
        ver[i].v=i;
        fscanf(fp,"%d",&ver[i].x);
        DataError(ver[i].x);
        fscanf(fp,"%d",&ver[i].y);
        DataError(ver[i].y);
    }
    fclose(fp);
}
//边赋值
void EnWeight(Edge &edg,Vertex ver)
{
    int k=0;
    for(int i=0;i<N;i++)
    {//头为i
        for(int j=0;j<i;j++)
        {//尾为j
            edg[k].bgn=ver[i].v;
            edg[k].end=ver[j].v;
            edg[k].weight=sqrt(pow(ver[i].x-ver[j].x,2)+pow(ver[i].y-ver[j].y,2));
            k++;
        }
    }
}
bool cmp(node1 a,node1 b)
{
    return a.weight<b.weight;
}
//排序
void Range(Edge &edg)
{
    sort(edg,edg+n_edge,cmp);
}
//调适数据
void Show(Vertex ver,Edge edg)
{
    printf("序号\tx\ty\t\n");
    for(int i=0;i<N;i++)    printf("%d\t%d\t%d\t\n",ver[i].v,ver[i].x,ver[i].y);
    printf("头\t尾\t权值\t\n");
    for(int i=0;i<n_edge;i++)   printf("%d\t%d\t%lf\n",edg[i].bgn,edg[i].end,edg[i].weight);
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            cout<<Graph[i][j]<<" ";
        cout<<endl;
    }
}
int Find(int father[],int f)
{
    while(father[f]>-1)  f=father[f];
    return f;
}
/********************************************
    1.距离小于10 联通，不建桥，不花钱
    2.距离大于1000 不联通
    3.若搜索到距离大于1000的边，且百岛湖
      未联通，则输出no
********************************************/
//kruskal算法
double Kruskal(Edge edg)
{
    int father[n_edge],bnf,edf,i,linked=0;
    double sum=0;
    for(i=0;i<n_edge;i++)   father[i]=-1;
    for(i=0;i<n_edge&&linked<N-1;i++)
    {
        if(edg[i].weight>=1000)
        {
            cout<<"no!"<<endl;
            exit(0);
        }
        bnf=Find(father,edg[i].bgn);
        edf=Find(father,edg[i].end);
        if(bnf!=edf)
        {//两图不联通,建立通路
            father[bnf]=edf;
            linked++;
            if(edg[i].weight>=10)
            {//需要建桥
                sum+=edg[i].weight;
                Graph[edg[i].bgn][edg[i].end]=true;
                /**Warning！数组下标*/
            }
        }
    }
    return sum;
}
int main()
{
    Edge edg;
    Vertex ver;
    double sum;
    FInput(ver);//从文件读入坐标
    EnWeight(edg,ver);//计算权值并赋予边
    Range(edg);//排序
    //Show(ver,edg);
    sum=Kruskal(edg);
    sum*=100;
    //Show(ver,edg);
    cout<<"建桥策略如下："<<endl;
    for(int i=0;i<N;i++)
        for(int j=0;j<i;j++)
            if(Graph[i][j])
                printf("(%d,%d)-(%d,%d)\n",ver[i].x,ver[i].y,ver[j].x,ver[j].y);
    cout<<"总造价为："<<sum<<endl;
    return 0;
}
