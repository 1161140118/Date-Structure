#include <iostream>
#define MAX 1000     //����
#define MIN -1      //��С
#define N 8         //˳����
#define M 3         //ÿ��˳���е�Ԫ������

using namespace std;

/**********************************************
1.�����飬�ϸ�ע��߽�����
2.���㷨�޸Ĵ��룬�������ô���ȥ�������������
**********************************************/

typedef struct
{
    int val;  //��ǰ��˳�����������ֵ
    int p;  //˳���е�i����
}KEY;

//������
int CreatLoseTree(int ls[],KEY k[])
{
    int tmp;
    int flag=0;   //��������
    for (int i=0;i<N;i++)
    {//����˳����������
        flag=0;
        int order=i;//��order��˳��
        int parent=order+N-2;// parent/2 Ϊ˳�����ڵ�
        while (!flag)   //����Ϊls[N-1]
        {
            if(parent!=0)//δ����������
            {
                parent/=2;
                if (k[order].val>=k[ls[parent]].val) //��order���븸�ڵ���߱Ƚ� orderΪ����
                {
                    tmp=ls[parent];
                    ls[parent]=order;
                    order=tmp;  //orderΪʤ��
                }
            }
            else
            {
                parent=N-1;flag=1;//��־��������
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
//���ð�������˳������Ԫ������orderΪ�ϴ������˳����
int RunLoseTree(int ls[],KEY k[],int order,int R[N][M])
{
    cout<<k[order].val<<endl;  //�������ֵ

    if(k[order].p!=M-1)   //δȡ�����һ��ֵ
        k[order].val=R[order][++k[order].p];    //��order˳��ȡ��ֵ
    else
        k[order].val=MAX;   //��Ϊ���ֵ

    int tmp;
    //�Ե�order������
    int parent=order+N-1; // parent/2 Ϊ˳�����ڵ�
    int flag=0;
    while (!flag)   //����Ϊls[N-1]
    {
        if(parent!=0)//δ����������
        {
            parent/=2;
            if (k[order].val>=k[ls[parent]].val) //��order���븸�ڵ���߱Ƚ� orderΪ����
            {
                tmp=ls[parent];
                ls[parent]=order;
                order=tmp;  //orderΪʤ��
            }
        }
        else
        {
            parent=N-1;flag=1;//��־��������
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
    for (int i=0;i<N;i++) ls[i]=N;    //��ʼ�����а������ ls[N-1]Ϊ����
    for (int i=0;i<N;i++)
    {
        k[i].val=R[i][0]; //��ʼ����˳�����������Ԫ��
        k[i].p=0;
    }
    k[N].val=MIN;
    k[N].p=0;        //��ʼ����������

    int order;
    order=CreatLoseTree(ls,k);
    cout<<"Ԫ������:"<<endl;
    for(int i=0;i<M*N;i++)
    {
        order=RunLoseTree(ls,k,order,R);
    }

    return 0;
}
