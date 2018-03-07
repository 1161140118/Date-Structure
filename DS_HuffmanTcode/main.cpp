#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#define N 92    //ASCLL:32~122 ( space ~ z ) define: 123 \n

using namespace std;

typedef struct HTNODE
{//���ڵ�
    double weight;
    int lchild;//��֧Ϊ0
    int rchild;//��֧Ϊ1
    int parent;
}HuffmanT[2*N-1];//����������̬��������

typedef struct CodeNode
{//�ַ� Ȩ�� ����λ��
    double weight;
    char ch;
    char bits[N+1];
}HuffmanCode[N];//�����

//��ʼ����������
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
//��ʼ�������
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

//ͳ���ַ�,����Ȩֵ
void CountW(HuffmanCode H)
{
    FILE *fp=NULL;
    if( (fp=fopen("F:\\DS_FILE\\Article.txt","r")) ==NULL )
    {
        cout<<"Failure to open the file!"<<endl;
        exit(0);
    }
    double sum=0;//ͳ���ַ�����
    int flag=0;//��־��������Ƿ��и��ַ�
    char c;//�����ַ�c
    while(!feof(fp))
    {//��ȡ�ļ��ַ�
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
        {//����������Ƿ�c
            if(c==EOF)  break;//�����ļ�ĩβ
            cout<<"No '"<<c<<"' in the code"<<endl;
            printf("%d",c);
            exit(0);
        }
    }//while

    for(int i=0;i<N;i++)
    {//ȨֵС����
        H[i].weight/=sum;
    }
    fclose(fp);
}

//����Ȩֵ
void InputW(HuffmanT T,HuffmanCode H)
{
    for(int i=0;i<N;i++)
    {
        T[i].weight=H[i].weight;
    }
}

/**************************************
    1.Ȩ����С
    2.�Ǳ���С
    3.���ڵ㲻Ϊ-1
***************************************/
//0-n�� ѡ����Сֵ�ʹ�Сֵ
void MIN(HuffmanT T,int n,int &p1,int &p2)
{
    double tmp;
    p1=0;p2=1;//��ʼ��

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
    {//p1��С
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
    {//p2��С
        if(i==p1)   continue;
        if(T[i].weight<tmp&&T[i].parent==-1)
        {
            tmp=T[i].weight;
            p2=i;
        }
    }
}

//�����������
void CreatHuffmanT(HuffmanT T)
{
    int i,p1,p2;//ɨ�����p1,p2
    for(i=N;i<2*N-1;i++)//n-1�κϲ�
    {

        MIN(T,i,p1,p2);//0~i-1����Сֵ�ʹ�Сֵ
        T[p1].parent=i;
        T[p2].parent=i;
        T[i].lchild=p1;
        T[i].rchild=p2;
        T[i].weight=T[p1].weight+T[p2].weight;
    }
}

//����
void Encoding(HuffmanT T,HuffmanCode H)
{
    int c,p,i;//c��p�ֱ�ָʾT�к��Ӻ�˫�׵�λ��
    char cd[N+1];
    int start;//ָʾ������cd�е�λ��
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
            //��T[c]��T[p]�����ӣ������ɴ���0���������ɴ���1
            c=p;    //��������
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

//����
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
    int child=2*N-2;//�ӽڵ�
    while(!feof(fpr))
    {//����01
        ch=fgetc(fpr);
        if(ch=='0')
            child=T[child].lchild;
        else
            child=T[child].rchild;

        if(child<=N-1 && child>=0)
        {//Ҷ�ڵ�
            fputc(H[child].ch,fpw);
            child=2*N-2;
        }
    }
}


int main()
{
    HuffmanT    T;//��������T
    HuffmanCode H;//�����������H
    InitializeHT(T);//��ʼ����
    InitializeHC(H);//��ʼ�������

    CountW(H);
    InputW(T,H);//����Ȩֵ
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
