#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include "dfqueue.h"
#define N 10

using namespace std;

struct MTGraph
{
    int verlist[N];//�����
    int edge[N][N];//�߱�
    int n,e;//������������
};

//���ļ�����ͼ
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

    cout<<"�ڽӾ�������:"<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            cout<<G.edge[i][j]<<' ';
        cout<<endl;
    }
    cout<<endl;
}

/*******************
    ������ȱ���
********************/
bool visited[N];
int dfn[N];
//��һ�������������������
//�ݹ��㷨
void DFS_re(MTGraph G,int i)
{
    int j;
    static int cnt=1;//���
    cout<<G.verlist[i]<<' ';//visit i
    visited[i]=true;
    dfn[i]=cnt;//�� vi ���
    cnt++;
    for(j=0;j<G.n;j++)
        if( (G.edge[i][j]==1)&& !visited[j] )
            DFS_re(G,j);
}
//�ǵݹ��㷨 ջ����
void DFS_inre(MTGraph G,int k)
{
    stack <int> S;
    int i,j;
    S.push(k);
    visited[k]=true;
    cout<<G.verlist[k]<<' ';

    S.push(k);//Ϊѭ������
    while(!S.empty())
    {//ջ�ǿ�ʱ��������
        i=S.top();
        S.pop();
        for(j=0;j<G.n;j++)
        {//����vi���ٽӵ�vj
            if( G.edge[i][j]==1 && !visited[j] )
            {//��vjδ���ʹ�
                cout<<G.verlist[j]<<' ';
                visited[j]=true;//���ʹ�vj
                S.push(j);
                i=j;//���
            }
        }//for
    }//while
}
//���㷨
void DFSTraverse(MTGraph G)
{
    cout<<"DFS(recursion):"<<endl;
    int i;
    for(i=0;i<G.n;i++)
        visited[i]=false;
    for(i=0;i<G.n;i++)
        if(!visited[i])
            DFS_re(G,i);//�Ӷ���i��������������
    cout<<endl;

    cout<<"DFS(inrecursion):"<<endl;
    for(i=0;i<G.n;i++)
        visited[i]=false;
    for(i=0;i<G.n;i++)
        if(!visited[i])
            DFS_inre(G,i);//�Ӷ���i��������������
    cout<<endl;
}




/*******************
    ������ȱ���
********************/
//��vkΪ�����㣬�����ȹ�����
void BFS2(MTGraph G,int k)
{
    int i,j;//��ǰ���������ڽӶ���
    Que Q;
    MakeNull(Q);

    cout<<G.verlist[k]<<' ';
    visited[k]=true;
    EnQueue(k,Q);

    while(!Empty(Q))
    {//�ӿ�ʱ��������
        i=DeQueue(Q);//vi����
        for(j=0;j<G.n;j++)
        {//����vi���ٽӵ�vj
            if( G.edge[i][j]==1 && !visited[j] )
            {//��vjδ���ʹ�
                cout<<G.verlist[j]<<' ';
                visited[j]=true;//���ʹ�vj
                EnQueue(j,Q);//���ʹ����
            }
        }//for ���vi�������ڽӶ���
    }//while �ж϶����Ƿ�Ϊ��
}
//���㷨
void BFSTraverse(MTGraph G)
{
    cout<<"BFS:"<<endl;
    int i;
    for(i=0;i<G.n;i++)
        visited[i]=false;
    for(i=0;i<G.n;i++)//����ͬʱѭ��������
        if(!visited[i])
            BFS2(G,i);//�Ӷ���i��������������
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
