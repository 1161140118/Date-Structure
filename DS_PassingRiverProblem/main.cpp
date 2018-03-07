#include <iostream>
#include <queue>
#define N 16
using namespace std;

/***********************
    1�԰�  ��   0��
    1   1   1   1
    ũ  ��  ��  ��

************************/

//�ж�λ��
bool farmer(int location)
{
    return location&0x8;
}
bool wolf(int location)
{
    return location&0x4;
}
bool cabbage(int location)
{
    return location&0x2;
}
bool goat(int location)
{
    return location&0x1;
}

//�жϰ�ȫ
bool IsSafe(int location)
{
    //���ͬ�࣬��ũ��
    if( (goat(location) == cabbage(location)) && (goat(location) != farmer(location)) )
        return false;
    //����ͬ�࣬��ũ��
    if( (goat(location) == wolf(location)) && (goat(location) != farmer(location)) )
        return false;
    //����״̬��ȫ
    return true;
}



int main()
{

    int location=0,newlocation;
    queue <int> MOVE;//���м�¼���԰�ȫ������м�״̬
    int route[N];//���ڼ�¼�ѿ��ǵ�״̬·��
    for(int i=0;i<N;i++)
    {//��ʼ��
        route[i]=-1;
    }
    route[0]=0;
    MOVE.push(location);//��ʼ״̬���
    while( !MOVE.empty() && (route[N-1]==-1) )
    {//���зǿ���δ��ȫ����
        location=MOVE.front();//ȡ������Ϊ��ǰ״̬��������һ����й�ȱ���
        MOVE.pop();
        for(int i=1;i<=8;i<<=1)
        {//λ���ƶ�
            if(farmer(location)==((location&i)!=0))
            {//ũ�����ƶ���ͬ��
                newlocation=location^(i|0x8);//ũ������Ʒͬʱ�ƶ����ó���״̬
                if(IsSafe(newlocation)&&(route[newlocation]==-1))
                {//��״̬��ȫ����δ����
                    route[newlocation]=location;//��¼��״̬��ǰ��
                    MOVE.push(newlocation);//��״̬���
                }
            }
        }//for

        if(route[N-1]!=-1)
        {//��������״̬
            cout<<"���Ӳ��ԣ�"<<endl;
            for(location=15;location!=0;location=route[location])
            {
                newlocation=route[location];
                switch(location^newlocation)
                {//����ǰ��״̬�仯
                case 8:
                    cout<<"ũ�񵥶�����"<<endl;
                    break;
                case 9:
                    cout<<"ũ��������"<<endl;
                    break;
                case 10:
                    cout<<"ũ����˹���"<<endl;
                    break;
                case 12:
                    cout<<"ũ����ǹ���"<<endl;
                    break;
                default:
                    cout<<"error!"<<endl;
                }
            }
        }
    }
    return 0;
}
