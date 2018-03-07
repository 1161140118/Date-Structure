#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct datatype
{
    int key;//�ؼ���
    int rec;//��¼ֵ
};
typedef struct celltype
{
    datatype data;
    int cnt;//ͳ����ͬ����
    struct celltype *lchild,*rchild;
}BSTNode;
typedef BSTNode *BST;

//����
bool BST_Search(int k,BST F)
{
    BST p=F;
    if(p==NULL)
        return true;
    if(k==p->data.key)
    {
        cout<<"The data is "<<p->data.rec<<endl;
        return false;
    }
    if(k< p->data.key)
        return (BST_Search(k,p->lchild));
    else
        return (BST_Search(k,p->rchild));
}
//����
void BST_Insert(datatype R,BST &F)
{
    if(F==NULL)
    {
        F=new BSTNode;
        F->data=R;
        F->cnt =1;//��ʼ�ظ�ֵΪ1
        F->lchild=NULL;
        F->rchild=NULL;
    }
    else if(R.key< F->data.key)
        BST_Insert(R,F->lchild);
    else if(R.key> F->data.key)
        BST_Insert(R,F->rchild);
    else
        F->cnt++;//��¼�ظ�
}
//ɾ����Сֵ
datatype BST_deletemin(BST &F)
{
    datatype R;
    if(F->lchild==NULL)
    {
        BST p=F;
        R=F->data;
        F->rchild;
        delete p;
        return R;
    }
    else
        return (BST_deletemin(F->rchild));
}
//ɾ��
bool BST_Delete(int k,BST &F)
{
    if(F!=NULL)
    {
        if(k< F->data.key)
            BST_Delete(k,F->lchild);
        else if(k> F->data.key)
            BST_Delete(k,F->rchild);
        else
        {//k==F->data.key
            if(F->cnt > 1)
            {
                //cout<<F->data.key<<F->cnt<<endl;
                F->cnt --;
                return false;
            }
            if(F->rchild==NULL)
                F=F->lchild;
            else if(F->lchild==NULL)
                F=F->rchild;
            else
                F->data=BST_deletemin(F->rchild);
        }
        return false;
    }
    return true;//�ùؼ��ֲ�����
}
//���ļ�����BST
BST FBST_Creat()
{
    BST F=NULL;
    datatype R;//�ؼ�ֵ
    FILE *fp=NULL;
    if( (fp=fopen("BST.txt","r"))==NULL )
    {
        cout<<"error: Failure to open the file!"<<endl;
        exit(0);
    }
    while(1)
    {
        fscanf(fp,"%d",&R.key);
        if(R.key==0||feof(fp))    return F;/**�ؼ���Ϊ0���򷵻�*/
        fscanf(fp,"%d",&R.rec);
        BST_Insert(R,F);
    }
}
//�Ӽ��̼���
BST BST_Creat()
{
    BST F=NULL;
    datatype R;//�ؼ�ֵ
    cout<<"���� 0 ֹͣ����..."<<endl;
    while(1)
    {
        scanf("%d",&R.key);
        if(R.key==0)    return F;/**�ؼ���Ϊ0���򷵻�*/
        scanf("%d",&R.rec);
        BST_Insert(R,F);
    }
}

//�ݹ��������
void inOrder(BST root)
{
    if (root==NULL)
        return;
    inOrder(root->lchild);
    cout<<root->data.key;
    if(root->cnt >1)
        cout<<"("<<root->cnt<<")";
    cout<<endl;
    inOrder(root->rchild);
}

//ɾ����
void BST_Destory(BST &F)
{
    if(F!=NULL)
    {
        BST_Destory(F->lchild);
        BST_Destory(F->rchild);
        delete F;
    }
}


int main()
{
    BST F=NULL;
    int k;//���� ɾ��
    datatype R;//����
    int flag=1;     //��־��״̬
    int opt=-1;     //ѡ�����
    while(1)
    {
        if(F==NULL) flag=1;
        printf("*****************�˵���*******************\n");
        if(flag==1)
        {
        printf("    1.���ļ���������\n");
        printf("    2.�Ӽ�����������\n");
        printf("    0.�˳�\n");
        }
        if(flag==2)
        {
        printf("    3.�鿴ȫ���ؼ���\n");
        printf("    4.��������\n");
        printf("    5.��������\n");
        printf("    6.ɾ������\n");
        printf("    7.�������\n");
        printf("    0.�˳�\n");
        }
        printf("******************************************\n");

        printf("��������ţ�");
        scanf("%d",&opt);

        if(flag==1)
        {
            switch(opt)
            {
            case 0:
                exit(0);
            case 1:
                F=FBST_Creat();
                flag=2;
                system("cls");
                break;
            case 2:
                F=BST_Creat();
                flag=2;
                system("cls");
                break;
            default:
                cout<<"��������ȷ��ţ�"<<endl;
                break;
            }
        }
        else
        {
            switch(opt)
            {
            case 0:
                BST_Destory(F);
                exit(0);
            case 3:
                inOrder(F);
                break;
            case 4:
                cout<<"������:�ؼ���ֵ ����ֵ"<<endl;
                cin>>R.key>>R.rec;
                BST_Insert(R,F);
                break;
            case 5:
                cout<<"�����ҹؼ���ֵ:"<<endl;
                cin>>k;
                if(BST_Search(k,F)) cout<<"error: Data error!"<<endl;
                break;
            case 6:
                cout<<"��ɾ���ؼ���ֵ:"<<endl;
                cin>>k;
                if(BST_Delete(k,F)) cout<<"error: Data error!"<<endl;
                break;
            case 7:
                BST_Destory(F);
                system("cls");
                flag=1;
                break;
            default:
                cout<<"��������ȷ��ţ�"<<endl;
            }
            putchar('\n');
        }


    }

    return 0;
}
