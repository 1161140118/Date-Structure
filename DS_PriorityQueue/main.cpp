#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 200
using namespace std;

/************************************
     �轨���ļ�F��\\task.dat
************************************/
struct process  //����
{
    int num;    //���������
    int pri;    //�������ȼ�
};

struct HEAP
{
    process pro[MaxSize];
    int n;      //����������
};

//����һ���ն�
void MaxHeap(HEAP &heap)
{
    heap.n=0;
}
//�ж϶��Ƿ�Ϊ��
bool HeapEmpty(HEAP heap)
{
    return (!heap.n);
}
//�ж϶��Ƿ�Ϊ��
bool HeapFull(HEAP heap)
{
    return (heap.n==MaxSize-1);
}
//����һ��Ԫ��
void Insert(HEAP &heap,process p)
{
    int i=0;
    if(!HeapFull(heap))     //�Ѳ���
    {
        heap.n++;
        i=heap.n;
        while((i!=1)&&(p.pri>heap.pro[i/2].pri))    //[i/2]Ϊi�ĸ��ڵ�
        {
            heap.pro[i]=heap.pro[i/2];
            i=i/2;
        }
        heap.pro[i]=p;
    }
    else
        cout<<"����ʧ�ܣ���������"<<endl;
}
//ɾ���Ѷ�Ԫ��
process DeleteMax(HEAP &heap)
{
    int parent=1,child=2;
    process p,tmp;
    if(!HeapEmpty(heap))
    {
        p=heap.pro[1];
        tmp=heap.pro[heap.n--]; //�����ĩԪ��
        while(child<=heap.n)
        {/*�ӶѶ���ʼ����Ԫ��������ϴ�*/
            if( (child<heap.n)&&(heap.pro[child].pri<heap.pro[child+1].pri) )   //�ϴ�����
                child++;
            if(tmp.pri>heap.pro[child].pri)    //����ĩԪ�ؽϴ� ����ڵ�λ��
                break;
            heap.pro[parent]=heap.pro[child];
            parent=child;   //ѡ���֧
            child*=2;       //ɨ����һ��
        }//while
        heap.pro[parent]=tmp;   //�ö�ĩԪ�����ȱ
        return p;
    }//if
    return heap.pro[0];
}
/*
void Input(HEAP &heap)
{
    int num,pri,i;
    process tmp;
    cout<<"������ ��������� �������ȼ������븺ֵֹͣ��"<<endl;
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
    cout<<"������ɣ�"<<endl;
    for(i=1;i<=heap.n;i++)
    {
        cout<<heap.pro[i].num<<' '<<heap.pro[i].pri<<endl;
    }
    putchar('\n');
}
*/
//���ļ�����
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
    {//����
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
    cout<<"������ɣ�"<<endl;
    putchar('\n');
    fclose(fp);
}
//��������
bool cmp(process a,process b)
{
    if(a.pri!=b.pri) return a.pri>b.pri;
    return a.num<b.num;
}
//�������
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

    sort(tmp,tmp+n,cmp);    //�����鰴cmp����
    cout<<"�����������:"<<endl;
    cout<<"����� ���ȼ�"<<endl;
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