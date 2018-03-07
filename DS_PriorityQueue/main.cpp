#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 200
using namespace std;

/************************************
     需建立文件F：\\task.dat
************************************/
struct process  //进程
{
    int num;    //进程任务号
    int pri;    //进程优先级
};

struct HEAP
{
    process pro[MaxSize];
    int n;      //堆中数据数
};

//创建一个空堆
void MaxHeap(HEAP &heap)
{
    heap.n=0;
}
//判断堆是否为空
bool HeapEmpty(HEAP heap)
{
    return (!heap.n);
}
//判断堆是否为满
bool HeapFull(HEAP heap)
{
    return (heap.n==MaxSize-1);
}
//插入一个元素
void Insert(HEAP &heap,process p)
{
    int i=0;
    if(!HeapFull(heap))     //堆不满
    {
        heap.n++;
        i=heap.n;
        while((i!=1)&&(p.pri>heap.pro[i/2].pri))    //[i/2]为i的父节点
        {
            heap.pro[i]=heap.pro[i/2];
            i=i/2;
        }
        heap.pro[i]=p;
    }
    else
        cout<<"插入失败，堆已满！"<<endl;
}
//删除堆顶元素
process DeleteMax(HEAP &heap)
{
    int parent=1,child=2;
    process p,tmp;
    if(!HeapEmpty(heap))
    {
        p=heap.pro[1];
        tmp=heap.pro[heap.n--]; //保存堆末元素
        while(child<=heap.n)
        {/*从堆顶开始，将元素逐层向上串*/
            if( (child<heap.n)&&(heap.pro[child].pri<heap.pro[child+1].pri) )   //较大子树
                child++;
            if(tmp.pri>heap.pro[child].pri)    //若堆末元素较大 则填补节点位置
                break;
            heap.pro[parent]=heap.pro[child];
            parent=child;   //选择分支
            child*=2;       //扫描下一层
        }//while
        heap.pro[parent]=tmp;   //用堆末元素填补空缺
        return p;
    }//if
    return heap.pro[0];
}
/*
void Input(HEAP &heap)
{
    int num,pri,i;
    process tmp;
    cout<<"请输入 进程任务号 进程优先级（输入负值停止）"<<endl;
    while(1)
    {
        if(heap.n==MaxSize) break;
        cin>>num;
        if(num<0) break;
        cin>>pri;
        if(pri<0) break;

        tmp.num=num;
        tmp.pri=pri;
        Insert(heap,tmp);

    }
    cout<<"输入完成！"<<endl;
    for(i=1;i<=heap.n;i++)
    {
        cout<<heap.pro[i].num<<' '<<heap.pro[i].pri<<endl;
    }
    putchar('\n');
}
*/
//从文件读入
void FInput(HEAP &heap)
{
    FILE *fp=NULL;
    if((fp=fopen("F:\\task.dat","r"))==NULL)
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    int num,pri;
    process tmp;
    while(!feof(fp))
    {//读入
        if(heap.n==MaxSize) break;
        fscanf(fp,"%d",&num);
        cout<<num<<' ';
        if(num<0) break;
        fscanf(fp,"%d",&pri);
        cout<<pri<<' '<<endl;
        if(pri<0) break;

        tmp.num=num;
        tmp.pri=pri;
        Insert(heap,tmp);

    }
    cout<<"输入完成！"<<endl;
    putchar('\n');
    fclose(fp);
}
//排序依据
bool cmp(process a,process b)
{
    if(a.pri!=b.pri) return a.pri>b.pri;
    return a.num<b.num;
}
//整理输出
void Output(HEAP &heap)
{
    int n=heap.n;
    process *tmp=NULL;
    tmp=new process[n];
    int i;
    for(i=0;i<n;i++)
    {
        tmp[i]=DeleteMax(heap);

    }

    sort(tmp,tmp+n,cmp);    //对数组按cmp排序
    cout<<"输出序列如下:"<<endl;
    cout<<"任务号 优先级"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"   "<<tmp[i].num<<"     "<<tmp[i].pri<<endl;
    }
}

int main()
{
    HEAP heap;
    MaxHeap(heap);
    FInput(heap);
    Output(heap);

    return 0;
}
