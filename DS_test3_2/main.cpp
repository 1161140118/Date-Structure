#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#define INFINITY 1000

using namespace std;

/*******************************************
    1.new type(n)   �����ڴ棬ֵ��ʼ��Ϊ0
    2.new type[n]   �����ڴ棬n*size_of(type)
    3.delete [] a   �ͷ������ڴ� ע�� []
*******************************************/

int n;//������
bool *S;//���Դ��������ɵ��յ�
int *D;//D[i]��ʾԴ��1������i�ĵ�ǰ���·������
int *P;//P[i]��ʾԴ��1������i�ĵ�ǰ���·���ϣ���󾭹��Ķ���
int **C;//ͼ

//ֱ������
void Input()
{
    cout<<"������ƻ�������";
    cin>>n;
    if(n<2)
    {
        cout<<"���ݴ���"<<endl;
        exit(0);
    }
    n++;
    cout<<"�豸���"<<endl;
    int price_buy[n];
    int price_maintain[n];
    for(int i=1;i<n;i++)
    {
        cout<<"��"<<i<<"����ۣ�";
        cin>>price_buy[i];
        if(price_buy[i]<=0)
        {
            cout<<"���ݴ���"<<endl;
            exit(0);
        }
    }
    for(int i=1;i<n;i++)
    {
        printf("��%d-%d��ά�޷��ã�",i-1,i);
        cin>>price_maintain[i];
        if(price_maintain[i]<=0)
        {
            cout<<"���ݴ���"<<endl;
            exit(0);
        }
    }
    //��ʼ��S
    S=new bool[n+1];
    S[1]=true;
    //��ʼ��P
    P=new int[n+1];
    //��ʼ��D
    D=new int[n+1];
    //��ʼ��ͼC
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

//�ļ�����
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
        cout<<"���ݴ���"<<endl;
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
            cout<<"���ݴ���"<<endl;
            exit(0);
        }
    }
    for(int i=1;i<n;i++)
    {
        fscanf(fp,"%d",&price_maintain[i]);
        if(price_maintain[i]<=0)
        {
            cout<<"���ݴ���"<<endl;
            exit(0);
        }
    }

    fclose(fp);

    //��ʼ��S
    S=new bool[n+1];
    S[1]=true;
    //��ʼ��P
    P=new int[n+1];
    //��ʼ��D
    D=new int[n+1];
    //��ʼ��ͼC
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

//������
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

//��S֮�⣬ѡȡһ������w��ʹD[w]��С
int MinCost(int *D,bool *S)
{
    int tmp=INFINITY;
    int w=2;
    for(int i=2;i<=n;i++)
        if(!S[i]&&D[i]<tmp)
        {//��i�����·��
            tmp=D[i];
            w=i;
        }
    return w;
}
//�Ͽ�˹���㷨
void Dijkstra(int **C,int *D,int *P,bool *S)
{
    int w,sum;
    for(int i=1;i<=n-1;i++)
    {
        w=MinCost(D,S);//ʹD[w]��С
        S[w]=true;//w��S
        for(int v=2;v<=n;v++)//����D
            if(!S[v])
            {//v����S-V
                sum=D[w]+C[w][v];
                if(sum<D[v])
                {//��w�����·����w��v��·��֮�ͱ����е�v�����·����С
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
    cout<<"**********�˵���*********"<<endl;
    cout<<"1.�ļ�����"<<endl;
    cout<<"2.����"<<endl;
    cout<<"*************************"<<endl;
    cout<<"���������..."<<endl;

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
            cout<<"������Ŵ������������룺"<<endl;
            cin>>op;
        }

    }

    Dijkstra(C,D,P,S);
    //show();
    int sum=0,i;
    stack <int> Y;
    Y.push(n);
    while(Y.top()!=1)//��������
        Y.push(P[Y.top()]);

    cout<<"�� 1";
    while(Y.top()!=n)
    {
        i=Y.top();
        Y.pop();
        if(i!=1)
            cout<<"��"<<i;
        sum+=C[i][Y.top()];
    }

    cout<<" �깺�����豸"<<endl;
    cout<<"�ܷ���Ϊ"<<sum<<"��Ԫ"<<endl;

    delete [] D;
    delete [] P;
    delete [] S;
    for(int i=0;i<=n;i++)
        delete [] C[i];
    delete [] C;
    return 0;
}
