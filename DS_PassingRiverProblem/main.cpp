#include <iostream>
#include <queue>
#define N 16
using namespace std;

/***********************
    1对岸  河   0岸
    1   1   1   1
    农  狼  白  羊

************************/

//判断位置
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

//判断安全
bool IsSafe(int location)
{
    //羊菜同侧，无农民
    if( (goat(location) == cabbage(location)) && (goat(location) != farmer(location)) )
        return false;
    //羊狼同侧，无农民
    if( (goat(location) == wolf(location)) && (goat(location) != farmer(location)) )
        return false;
    //其他状态安全
    return true;
}



int main()
{

    int location=0,newlocation;
    queue <int> MOVE;//队列记录可以安全到达的中间状态
    int route[N];//用于记录已考虑的状态路径
    for(int i=0;i<N;i++)
    {//初始化
        route[i]=-1;
    }
    route[0]=0;
    MOVE.push(location);//初始状态入队
    while( !MOVE.empty() && (route[N-1]==-1) )
    {//队列非空且未完全过河
        location=MOVE.front();//取队首作为当前状态，即对下一层进行广度遍历
        MOVE.pop();
        for(int i=1;i<=8;i<<=1)
        {//位置移动
            if(farmer(location)==((location&i)!=0))
            {//农夫与移动物同侧
                newlocation=location^(i|0x8);//农夫与物品同时移动，得出新状态
                if(IsSafe(newlocation)&&(route[newlocation]==-1))
                {//新状态安全，且未经历
                    route[newlocation]=location;//记录新状态的前驱
                    MOVE.push(newlocation);//新状态入队
                }
            }
        }//for

        if(route[N-1]!=-1)
        {//到达最终状态
            cout<<"过河策略："<<endl;
            for(location=15;location!=0;location=route[location])
            {
                newlocation=route[location];
                switch(location^newlocation)
                {//过河前后状态变化
                case 8:
                    cout<<"农民单独过河"<<endl;
                    break;
                case 9:
                    cout<<"农民带羊过河"<<endl;
                    break;
                case 10:
                    cout<<"农民带菜过河"<<endl;
                    break;
                case 12:
                    cout<<"农民带狼过河"<<endl;
                    break;
                default:
                    cout<<"error!"<<endl;
                }
            }
        }
    }
    return 0;
}
