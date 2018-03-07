#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#define INFINITY 1000

using namespace std;

/*******************************************
    1.new type(n)   申请内存，值初始化为0
    2.new type[n]   申请内存，n*size_of(type)
    3.delete [] a   释放数组内存 注意 []
*******************************************/

int n;//顶点数
bool *S;//存放源点和已生成的终点
int *D;//D[i]表示源点1到顶点i的当前最短路径长度
int *P;//P[i]表示源点1到顶点i的当前最短路径上，最后经过的顶点
int **C;//图

//直接输入
void Input()
{
    cout<<"请输入计划年数：";
    cin>>n;
    if(n<2)
    {
        cout<<"数据错误！"<<endl;
        exit(0);
    }
    n++;
    cout<<"设备造价"<<endl;
    int price_buy[n];
    int price_maintain[n];
    for(int i=1;i<n;i++)
    {
        cout<<"第"<<i<<"年造价：";
        cin>>price_buy[i];
        if(price_buy[i]<=0)
        {
            cout<<"数据错误！"<<endl;
            exit(0);
        }
    }
    for(int i=1;i<n;i++)
    {
        printf("第%d-%d年维修费用：",i-1,i);
        cin>>price_maintain[i];
        if(price_maintain[i]<=0)
        {
            cout<<"数据错误！"<<endl;
            exit(0);
        }
    }
    //初始化S
    S=new bool[n+1];
    S[1]=true;
    //初始化P
    P=new int[n+1];
    //初始化D
    D=new int[n+1];
    //初始化图C
    C=new int*[n+1];
    for(int i=0;i<=n;i++)
        C[i]=new int[n+1];
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
            C[i][j]=INFINITY;
        for(int j=i+1;j<=n;j++)
        {
            sum=price_buy[i];
            for(int k=1;k<=j-i;k++)
                sum+=price_maintain[k];
            C[i][j]=sum;
        }
    }
    for(int i=2;i<=n;i++)
    {
        D[i]=C[1][i];
        S[i]=false;
        P[i]=1;
    }
}

//文件读入
void FInput()
{
    FILE *fp;
    if( (fp=fopen("F:\\DS_FILE\\DS_test3_2.txt","r"))==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    fscanf(fp,"%d",&n);
    if(n<2)
    {
        cout<<"数据错误！"<<endl;
        exit(0);
    }
    n++;
    int price_buy[n];
    int price_maintain[n];
    for(int i=1;i<n;i++)
    {
        fscanf(fp,"%d",&price_buy[i]);
        if(price_buy[i]<=0)
        {
            cout<<"数据错误！"<<endl;
            exit(0);
        }
    }
    for(int i=1;i<n;i++)
    {
        fscanf(fp,"%d",&price_maintain[i]);
        if(price_maintain[i]<=0)
        {
            cout<<"数据错误！"<<endl;
            exit(0);
        }
    }

    fclose(fp);

    //初始化S
    S=new bool[n+1];
    S[1]=true;
    //初始化P
    P=new int[n+1];
    //初始化D
    D=new int[n+1];
    //初始化图C
    C=new int*[n+1];
    for(int i=0;i<=n;i++)
        C[i]=new int[n+1];
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
            C[i][j]=INFINITY;
        for(int j=i+1;j<=n;j++)
        {
            sum=price_buy[i];
            for(int k=1;k<=j-i;k++)
                sum+=price_maintain[k];
            C[i][j]=sum;
        }
    }
    for(int i=2;i<=n;i++)
    {
        D[i]=C[1][i];
        S[i]=false;
        P[i]=1;
    }

}

//调适用
void show()
{
    cout<<"D:"<<endl;
    for(int i=2;i<=n;i++)
        cout<<D[i]<<' ';
    cout<<endl;

    cout<<"P:"<<endl;
    for(int i=2;i<=n;i++)
        cout<<P[i]<<' ';
    cout<<endl;

    cout<<"S:"<<endl;
    for(int i=1;i<=n;i++)
        cout<<S[i]<<' ';
    cout<<endl;

    cout<<"C:"<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            cout<<C[i][j]<<' ';
        cout<<endl;
    }
}

//从S之外，选取一个顶点w，使D[w]最小
int MinCost(int *D,bool *S)
{
    int tmp=INFINITY;
    int w=2;
    for(int i=2;i<=n;i++)
        if(!S[i]&&D[i]<tmp)
        {//到i的最短路径
            tmp=D[i];
            w=i;
        }
    return w;
}
//迪克斯彻算法
void Dijkstra(int **C,int *D,int *P,bool *S)
{
    int w,sum;
    for(int i=1;i<=n-1;i++)
    {
        w=MinCost(D,S);//使D[w]最小
        S[w]=true;//w入S
        for(int v=2;v<=n;v++)//更新D
            if(!S[v])
            {//v属于S-V
                sum=D[w]+C[w][v];
                if(sum<D[v])
                {//到w的最短路径与w到v的路径之和比现有到v的最短路径更小
                    D[v]=sum;
                    P[v]=w;
                }
            }
    }
}

int main()
{
    int op;
    int flag=1;
    cout<<"**********菜单栏*********"<<endl;
    cout<<"1.文件读入"<<endl;
    cout<<"2.输入"<<endl;
    cout<<"*************************"<<endl;
    cout<<"请输入序号..."<<endl;

    while(flag)
    {
        cin>>op;
        switch(op)
        {
        case 1:
            FInput();
            flag=0;
            break;
        case 2:
            Input();
            flag=0;
            break;
        default:
            cout<<"输入序号错误，请重新输入："<<endl;
            cin>>op;
        }

    }

    Dijkstra(C,D,P,S);
    //show();
    int sum=0,i;
    stack <int> Y;
    Y.push(n);
    while(Y.top()!=1)//计算序列
        Y.push(P[Y.top()]);

    cout<<"第 1";
    while(Y.top()!=n)
    {
        i=Y.top();
        Y.pop();
        if(i!=1)
            cout<<"、"<<i;
        sum+=C[i][Y.top()];
    }

    cout<<" 年购置新设备"<<endl;
    cout<<"总费用为"<<sum<<"万元"<<endl;

    delete [] D;
    delete [] P;
    delete [] S;
    for(int i=0;i<=n;i++)
        delete [] C[i];
    delete [] C;
    return 0;
}
