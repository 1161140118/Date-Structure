#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <string.h>
#define M 8
#define N 8

using namespace std;

//��ǰ��
struct POINTER
{
    int pi;//��i��
    int pj;//��j��
};
//�Թ�
struct MAZE
{
    int Graph[M][N];//����ͼ
    //int Path[M][N];//·��ͼ
    POINTER Pre[M][N];//i,j��ǰ��
};

//���ļ�����ͼ
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
//��ʾͼ��Ϣ
void show(MAZE G)
{
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
            cout<<G.Graph[i][j]<<" ";
        cout<<endl;
    }
}
//�ж��Ƿ�ɵ���ɵ������,�ӵ㣨1��1����ʼ����
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
                G.Graph[tmp.pi][tmp.pj]=2;//�߹����2
                Q.push(tmp);//��Ӹõ�
                G.Pre[tmp.pi][tmp.pj]=P;
            }
        }
}

//�����������
void BFS(MAZE &G,queue <POINTER> &Q)
{
    POINTER head,out,P;
    P.pi=1;P.pj=1;
    out.pi=M-1;out.pj=N-1;
    head.pi=0;head.pj=0;
    if(G.Graph[P.pi][P.pj]!=0)
    {
        cout<<"�Թ��Ƿ���"<<endl;
        exit(0);
    }
    G.Pre[P.pi][P.pj]=head;//���ã�1��1����ǰ��Ϊ��0��0��
    G.Graph[P.pi][P.pj]=2;//��־�߹�
    G.Graph[0][0]=2;//��־�߹�
    while(!((P.pi==out.pi)&&(P.pj==out.pj)) )
    {//���зǿ���δ���յ�
        Reachable(P,G,Q);
        if(Q.empty())
        {
            cout<<"�޳��ڣ�"<<endl;
            exit(0);
        }
        P=Q.front();
        Q.pop();
    }
}
//�ݹ�����Թ�
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
    cout<<"�Թ����£���Ŀ¼���ı����룩"<<endl;
    FInput(G);
    show(G);
    BFS(G,Q);
    cout<<"����·��Ϊ��"<<endl;
    view(G,M-1,N-1);
    return 0;
}
