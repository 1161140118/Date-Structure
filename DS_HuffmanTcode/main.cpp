#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#define N 92    //ASCLL:32~122 ( space ~ z ) define: 123 \n

using namespace std;

typedef struct HTNODE
{//树节点
    double weight;
    int lchild;//左支为0
    int rchild;//右支为1
    int parent;
}HuffmanT[2*N-1];//哈夫曼树静态三叉链表

typedef struct CodeNode
{//字符 权重 编码位串
    double weight;
    char ch;
    char bits[N+1];
}HuffmanCode[N];//编码表

//初始化哈夫曼树
void InitializeHT(HuffmanT T)
{
    for(int i=0;i<2*N-1;i++)
    {
        T[i].parent=-1;
        T[i].lchild=-1;
        T[i].rchild=-1;
        T[i].weight=0;
    }
}
//初始化编码表
void InitializeHC(HuffmanCode H)
{
    for(int i=0;i<N-1;i++)
    {
        H[i].ch=' '+i;
        H[i].weight=0;
    }
    H[N-1].ch='\n';
    H[N-1].weight=0;
    if(H[N-2].ch=='z')
        cout<<"Success to Initialize!"<<endl;
    else
        cout<<"Failure to Initialize!"<<endl;
}

//统计字符,计算权值
void CountW(HuffmanCode H)
{
    FILE *fp=NULL;
    if( (fp=fopen("F:\\DS_FILE\\Article.txt","r")) ==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    double sum=0;//统计字符总数
    int flag=0;//标志编码表中是否有该字符
    char c;//读入字符c
    while(!feof(fp))
    {//读取文件字符
        c=fgetc(fp);
        flag=0;
        for(int i=0;i<N;i++)
        {
            if(c==H[i].ch)
            {
                H[i].weight++;
                sum++;
                flag=1;
                break;
            }
        }
        if(!flag)
        {//检查编码表中是否含c
            if(c==EOF)  break;//读到文件末尾
            cout<<"No '"<<c<<"' in the code"<<endl;
            printf("%d",c);
            exit(0);
        }
    }//while

    for(int i=0;i<N;i++)
    {//权值小数化
        H[i].weight/=sum;
    }
    fclose(fp);
}

//输入权值
void InputW(HuffmanT T,HuffmanCode H)
{
    for(int i=0;i<N;i++)
    {
        T[i].weight=H[i].weight;
    }
}

/**************************************
    1.权重最小
    2.角标最小
    3.父节点不为-1
***************************************/
//0-n中 选择最小值和次小值
void MIN(HuffmanT T,int n,int &p1,int &p2)
{
    double tmp;
    p1=0;p2=1;//初始化

    for(int i=0;i<n;i++)
    {
        if(T[i].parent==-1 && T[i].weight!=0)
        {
            p1=i;
            break;
        }
    }
    tmp=T[p1].weight;
    for(int i=0;i<n;i++)
    {//p1最小
        if(T[i].weight<tmp&&T[i].parent==-1)
        {
            tmp=T[i].weight;
            p1=i;
        }
    }

    for(int i=0;i<n;i++)
    {
        if(T[i].parent==-1 && i!=p1 && T[i].weight!=0)
        {
            p2=i;
            break;
        }
    }
    tmp=T[p2].weight;
    for(int i=0;i<n;i++)
    {//p2次小
        if(i==p1)   continue;
        if(T[i].weight<tmp&&T[i].parent==-1)
        {
            tmp=T[i].weight;
            p2=i;
        }
    }
}

//构造哈夫曼树
void CreatHuffmanT(HuffmanT T)
{
    int i,p1,p2;//扫描变量p1,p2
    for(i=N;i<2*N-1;i++)//n-1次合并
    {

        MIN(T,i,p1,p2);//0~i-1中最小值和次小值
        T[p1].parent=i;
        T[p2].parent=i;
        T[i].lchild=p1;
        T[i].rchild=p2;
        T[i].weight=T[p1].weight+T[p2].weight;
    }
}

//编码
void Encoding(HuffmanT T,HuffmanCode H)
{
    int c,p,i;//c和p分别指示T中孩子和双亲的位置
    char cd[N+1];
    int start;//指示编码在cd中的位置
    cd[N]='\0';

    FILE *fpr=NULL;
    if( (fpr=fopen("F:\\DS_FILE\\Article.txt","r")) ==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    FILE *fpw=NULL;
    if( (fpw=fopen("F:\\DS_FILE\\Article_encode.txt","w")) ==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }

    for(i=0;i<N;i++)
    {
        start=N;
        c=i;
        while( (p=T[c].parent)>=0 )
        {
            cd[--start]=(T[p].lchild==c)?'0':'1';
            //若T[c]是T[p]的左孩子，则生成代码0，否则生成代码1
            c=p;    //继续上溯
        }
        strcpy(H[i].bits,&cd[start]);
    }

    while(!feof(fpr))
    {
        int i;
        c=fgetc(fpr);
        if(c==EOF)
            break;
        else if(c=='\n')
            i=N-1;
        else if(c>=32&&c<=122)
            i=c-32;
        else
            exit(0);
        fputs(H[i].bits,fpw);
    }
    fclose(fpr);
    fclose(fpw);
}

//译码
void Decoding(HuffmanT T,HuffmanCode H)
{
    FILE *fpr,*fpw;
    if( (fpr=fopen("F:\\DS_FILE\\Article_encode.txt","r")) ==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    if( (fpw=fopen("F:\\DS_FILE\\Article_decode.txt","w")) ==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    char ch;
    int child=2*N-2;//子节点
    while(!feof(fpr))
    {//遍历01
        ch=fgetc(fpr);
        if(ch=='0')
            child=T[child].lchild;
        else
            child=T[child].rchild;

        if(child<=N-1 && child>=0)
        {//叶节点
            fputc(H[child].ch,fpw);
            child=2*N-2;
        }
    }
}


int main()
{
    HuffmanT    T;//哈夫曼树T
    HuffmanCode H;//哈夫曼编码表H
    InitializeHT(T);//初始化树
    InitializeHC(H);//初始化编码表

    CountW(H);
    InputW(T,H);//输入权值
    CreatHuffmanT(T);
    Encoding(T,H);
    Decoding(T,H);

    for(int i=0;i<N*2-1;i++)
    {
        if(T[i].weight!=0||i==175)
            cout<<i<<' '<<T[i].weight<<' '<<T[i].parent<<' '<<T[i].lchild<<' '<<T[i].rchild<<endl;
    }
    for(int i=0;i<N;i++)
    {
        if(H[i].weight!=0)
            cout<<H[i].ch<<' '<<H[i].bits<<endl;
    }
    return 0;
}
