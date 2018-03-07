#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct datatype
{
    int key;//关键字
    int rec;//记录值
};
typedef struct celltype
{
    datatype data;
    int cnt;//统计相同个数
    struct celltype *lchild,*rchild;
}BSTNode;
typedef BSTNode *BST;

//查找
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
//插入
void BST_Insert(datatype R,BST &F)
{
    if(F==NULL)
    {
        F=new BSTNode;
        F->data=R;
        F->cnt =1;//初始重复值为1
        F->lchild=NULL;
        F->rchild=NULL;
    }
    else if(R.key< F->data.key)
        BST_Insert(R,F->lchild);
    else if(R.key> F->data.key)
        BST_Insert(R,F->rchild);
    else
        F->cnt++;//记录重复
}
//删除最小值
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
//删除
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
    return true;//该关键字不存在
}
//从文件建立BST
BST FBST_Creat()
{
    BST F=NULL;
    datatype R;//关键值
    FILE *fp=NULL;
    if( (fp=fopen("BST.txt","r"))==NULL )
    {
        cout<<"error: Failure to open the file!"<<endl;
        exit(0);
    }
    while(1)
    {
        fscanf(fp,"%d",&R.key);
        if(R.key==0||feof(fp))    return F;/**关键字为0，则返回*/
        fscanf(fp,"%d",&R.rec);
        BST_Insert(R,F);
    }
}
//从键盘键入
BST BST_Creat()
{
    BST F=NULL;
    datatype R;//关键值
    cout<<"输入 0 停止输入..."<<endl;
    while(1)
    {
        scanf("%d",&R.key);
        if(R.key==0)    return F;/**关键字为0，则返回*/
        scanf("%d",&R.rec);
        BST_Insert(R,F);
    }
}

//递归中序遍历
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

//删除树
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
    int k;//查找 删除
    datatype R;//插入
    int flag=1;     //标志树状态
    int opt=-1;     //选择序号
    while(1)
    {
        if(F==NULL) flag=1;
        printf("*****************菜单栏*******************\n");
        if(flag==1)
        {
        printf("    1.从文件读入数据\n");
        printf("    2.从键盘输入数据\n");
        printf("    0.退出\n");
        }
        if(flag==2)
        {
        printf("    3.查看全部关键字\n");
        printf("    4.插入数据\n");
        printf("    5.查找数据\n");
        printf("    6.删除数据\n");
        printf("    7.清空数据\n");
        printf("    0.退出\n");
        }
        printf("******************************************\n");

        printf("请输入序号：");
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
                cout<<"请输入正确序号！"<<endl;
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
                cout<<"请输入:关键字值 数据值"<<endl;
                cin>>R.key>>R.rec;
                BST_Insert(R,F);
                break;
            case 5:
                cout<<"待查找关键字值:"<<endl;
                cin>>k;
                if(BST_Search(k,F)) cout<<"error: Data error!"<<endl;
                break;
            case 6:
                cout<<"待删除关键字值:"<<endl;
                cin>>k;
                if(BST_Delete(k,F)) cout<<"error: Data error!"<<endl;
                break;
            case 7:
                BST_Destory(F);
                system("cls");
                flag=1;
                break;
            default:
                cout<<"请输入正确序号！"<<endl;
            }
            putchar('\n');
        }


    }

    return 0;
}
