#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#define N 5    //������
using namespace std;
/***********************************
    1.������ʹ��û�������Ľṹ�壿
    2.���ضԴ������±�����
************************************/
//��
typedef struct node1
{
    int bgn;//ͷ����
    int end;//β����
    double weight;//Ȩֵ
}Edge[N*(N-1)/2+1];
/** ע�⣡ʵ����ΪN(N-1)/2���� */
int n_edge=N*(N-1)/2;

//��������
typedef struct node2
{
    int v;//�������
    int x;//���������
    int y;//����������
}Vertex[N];
bool Graph[N][N]={0};
void DataError(int a)
{
    if(a>1000||a<0)
    {
        cout<<"���ݴ��󣡣�0<=x,y<=1000��"<<endl;
        exit(0);
    }
}
//�ļ���������
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
//�߸�ֵ
void EnWeight(Edge &edg,Vertex ver)
{
    int k=0;
    for(int i=0;i<N;i++)
    {//ͷΪi
        for(int j=0;j<i;j++)
        {//βΪj
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
//����
void Range(Edge &edg)
{
    sort(edg,edg+n_edge,cmp);
}
//��������
void Show(Vertex ver,Edge edg)
{
    printf("���\tx\ty\t\n");
    for(int i=0;i<N;i++)    printf("%d\t%d\t%d\t\n",ver[i].v,ver[i].x,ver[i].y);
    printf("ͷ\tβ\tȨֵ\t\n");
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
    1.����С��10 ��ͨ�������ţ�����Ǯ
    2.�������1000 ����ͨ
    3.���������������1000�ıߣ��Ұٵ���
      δ��ͨ�������no
********************************************/
//kruskal�㷨
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
        {//��ͼ����ͨ,����ͨ·
            father[bnf]=edf;
            linked++;
            if(edg[i].weight>=10)
            {//��Ҫ����
                sum+=edg[i].weight;
                Graph[edg[i].bgn][edg[i].end]=true;
                /**Warning�������±�*/
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
    FInput(ver);//���ļ���������
    EnWeight(edg,ver);//����Ȩֵ�������
    Range(edg);//����
    //Show(ver,edg);
    sum=Kruskal(edg);
    sum*=100;
    //Show(ver,edg);
    cout<<"���Ų������£�"<<endl;
    for(int i=0;i<N;i++)
        for(int j=0;j<i;j++)
            if(Graph[i][j])
                printf("(%d,%d)-(%d,%d)\n",ver[i].x,ver[i].y,ver[j].x,ver[j].y);
    cout<<"�����Ϊ��"<<sum<<endl;
    return 0;
}
