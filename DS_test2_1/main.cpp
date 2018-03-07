#include <iostream>
#include <stack>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  N  100

using namespace std;

//�������ڵ�
struct BiTNode
{
    BiTNode *lchild;
    BiTNode *rchild;
    char    data;
};
typedef BiTNode* BITree;

/*
 *ǰ��������AB������������λ�ù�ϵ��
 *1.���ڵ�-��������...B(...)A...
 *2.���ڵ�-��������...AB...
 *3.������-��������...A...B...
*/

//������ ����ǰ������� �ǵݹ�
void createBiTree2(BITree &rT, string preStr, string inStr)
{
    BITree T=NULL;
    stack <BITree> sta;
    int index1=0,index2=0;
    int *preStrflag=NULL;
    preStrflag=new int(preStr.length());
    int i=0,j=0,k=0,m=0;
    preStr = preStr + '#';      //�����������в����ַ�����ʽ��ĩβ����#���ڴ���

    while (preStr[j] != '#')
    {   /*whileѭ���������Ӧ������ȫ�����Ϊ0*/
        preStrflag[j]=0;
        j++;
    }

    if (preStr.length() == 0 || inStr.length() == 0)
    {   /*�����������*/
        T = NULL;
        return;
    }

    else
    {  /*���ζ����������е�ÿ���ַ����д洢����һ��*/
        T = new BiTNode;T->lchild=NULL;T->rchild=NULL;
        rT=T;
        T->data = preStr[i];
        preStrflag[i]=1;
        i++;
        sta.push(T);
        while (preStr[i] != '#')
        {
            preStrflag[i]=1;
            if((index1 = inStr.find(preStr[i]))==-1)
            {
                cout<<"���ݴ���"<<endl;
                exit(0);
            }
            if((index2 = inStr.find(preStr[i-1]))==-1)
            {
                cout<<"���ݴ���"<<endl;
                exit(0);
            }
            if (index1 < index2)
            {/*���������������Ϊ...AB...,������Ϊ..B..A..,��Ϊ���ڵ���������*/
                T->lchild = new BiTNode;
                T=T->lchild;T->lchild=NULL;T->rchild=NULL;
                T->data = preStr[i];
                sta.push(T);
            }
            else if (index1 == index2 + 1)
            {/*���������������Ϊ...AB...,������Ϊ..AB..,�����ڵ���������������������*/
                T->rchild = new BiTNode;
                T=T->rchild;T->lchild=NULL;T->rchild=NULL;
                T->data = preStr[i];
                sta.push(T);
            }
            else
            {/*���������������Ϊ...AB...,������Ϊ..A..CB..*/
                k = inStr.find(preStr[i])-1;    //������ C ��λ��
                m = preStr.find(inStr[k]);      //
                while (preStrflag[m] == 0)      //���ַ���δ�����������ǵ�ǰ�ַ���������
                {/*��������������ǰ���������ҵ�һ���Ѵ������е��ַ������ַ���Ϊ���ڵ�*/
                    k--;
                    m = preStr.find(inStr[k]);
                }
                while (inStr[k] != T->data)     //��ջ���ҵ�C��������ǰ�ڵ����ΪC
                {
                    T= sta.top();
                    sta.pop();
                }
                T->rchild = new BiTNode;
                T=T->rchild;T->lchild=NULL;T->rchild=NULL;
                T->data = preStr[i];
                sta.push(T);
            }
            i++;
        }
    }
}

//  ջ�����
struct sstack {
    BITree db[N];
    int top;
};
struct QueueNode {
    BITree data;
    struct QueueNode* next;
};

//  �����еĶ��壬������ͷ�Ͷ�βָ��
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
}LinkQueue;
// �����еĳ�ʼ��
LinkQueue* InitQueue()
{
    LinkQueue* Que = (LinkQueue*)malloc(sizeof(LinkQueue));
    if (!Que)
    {
        printf("init Que error!\n");
        exit(0);
    }
    Que->front = (QueueNode*)malloc(sizeof(QueueNode));
    Que->front->next = NULL;
    Que->rear = Que->front;
    return Que;
}

// �����е����٣�ע���Ƚ�ȥ���Ƕ���ͷ�����ȥ���Ƕ���β
void DestoryQueue(LinkQueue* Que)
{
    while (Que->front)
    {
        Que->rear = Que->front->next;
        free(Que->front);
        Que->front = Que->rear;
    }
}
//���
void EnQueue(LinkQueue* Que, BITree node)
{
    QueueNode* queueNode = (QueueNode*)malloc(sizeof(QueueNode));
    queueNode->data = node;
    queueNode->next = NULL;
    Que->rear->next = queueNode;
    Que->rear = queueNode;
}
//����
BITree DeQueue(LinkQueue* Que)
{
    if (Que->front == Que->rear)//����Ϊ��
        return NULL;
    QueueNode* p = Que->front->next;
    BITree node = p->data;
    Que->front = p;
    return node;
}

//�������
void LayerOrderBiTree(BITree root)
{
    int curLayerCount = 0;      //��ǰ���еĽڵ���
    int nextLayerCount = 0;     //��һ���еĽڵ���
    struct Queue* Que = InitQueue();
    EnQueue(Que, root);
    curLayerCount++;
    BITree p;
    while ((p = DeQueue(Que)))
    {
        curLayerCount--;
        printf("%c ", p->data);
        if (p->lchild)
        {
            EnQueue(Que, p->lchild);
            nextLayerCount++;
        }
        if (p->rchild)
        {
            EnQueue(Que, p->rchild);
            nextLayerCount++;
        }
        if (curLayerCount == 0) //һ���Ѿ��������
        {
            curLayerCount = nextLayerCount;
            nextLayerCount = 0;
            printf("\n");
        }
    }
}
//�ǵݹ�������
void postTraverse(BITree t)
{
    BITree p, pre;
    p = t;
    pre = NULL;
    // ��ʼ��ջ
    sstack *s = (sstack *)malloc(sizeof(sstack));
    s->top = 0;

    while (p || s->top > 0) {
        if (p)
        {
            s->db[s->top ++] = p;
            p = p->lchild;
        }
        else
        {
            p = s->db[-- s->top];
            if (p->rchild != NULL && p->rchild != pre)
            { // pΪ��Ը��ڵ�
                s->db[s->top ++] = p;
                p = p->rchild;
            }
            else
            {
                printf("%c ", p->data);
                pre = p;
                p = NULL;
            }
        }
    }
}
//�ǵݹ��������
void feipreorderTraverse(BITree root)
{
    BITree p = root;
    // ��ʼ��ջ
    sstack *s = (sstack *)malloc(sizeof(sstack));
    s->top = 0;
    while (p || s->top > 0) {
        if (p)
        {
            printf("%c ", p->data);
            s->db[s->top ++] = p;
            p = p->lchild;
        }
        else
        {
            p = s->db[-- s->top];
            p = p->rchild;
        }
    }
}
//�ǵݹ��������
void feiinorderTraverse(BITree root)
{
    BITree p = root;
    // ��ʼ��ջ
    sstack *s = (sstack *)malloc(sizeof(sstack));
    s->top = 0;
    while (p || s->top > 0) {
        if (p)
        {
            s->db[s->top ++] = p;
            p = p->lchild;
        }
        else
        {
            p = s->db[-- s->top];
            printf("%c ", p->data);
            p = p->rchild;
        }
    }
}
//�ݹ��������
void preOrder(BITree root)
{
    if (root==NULL)
    {
        return;
    }
    printf("%c ",root->data);
    preOrder(root->lchild);
    preOrder(root->rchild);
}
//�ݹ�������
void postorder(BITree root)
{
    if (root==NULL)
    {
        return;
    }
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%c ",root->data);
}
//�ݹ��������
void inOrder(BITree root)
{
    if (root==NULL)
    {
        return;
    }
    inOrder(root->lchild);
    printf("%c ",root->data);
    inOrder(root->rchild);
}

//ɾ����
void Destory(BITree root)
{
    if(root!=NULL)
    {
        Destory(root->lchild);
        Destory(root->rchild);
        delete root;
    }
}

/************************************************************************/
/* �㷨
1��ͨ����������ҵ������A����ͨ��A�����������λ���ҳ���������������
2����A���������У����������ĸ���㣨���������ң���ת����1
3����A���������У����������ĸ���㣨���������ң���ת����1                                                                     */
/************************************************************************/

//���������������������ݹ鴴��������
BITree createBiTree(char *pre, char *in, int n)
{
    int i = 0;
    int n1 = 0,n2 = 0;
    int m1 = 0,m2 = 0;
    BITree node = NULL;
    char lpre[N],rpre[N];
    char lin[N],rin[N];
    int l=0,m;
    for (l=0;l<n;l++)
    {
        m=0;
        while(1)
        {
            if (pre[l]!=in[m])
                m++;
            if (pre[l]==in[m])
            {
                break;
            }
            if (m>=n)
            {
                printf("���ݴ���\n");
                exit(0);
            }
        }
    }

    if (n == 0)
    {
        return NULL;
    }
    node = (BiTNode*)malloc(sizeof(BiTNode));
    if (node==NULL)
    {
        return NULL;
    }
    memset(node,0,sizeof(BiTNode));
    //�������еĵ�һ��Ԫ�ر�Ϊ�����
    node->data = pre[0];
    //���ݸ���㽫�������з�Ϊ��������������
    for (i = 0;i<n;i++)
    {
        if ((i<=n1)&&(in[i]!=pre[0]))
        {
            lin[n1++] = in[i];//�ҵ����ڵ��������е�λ�ôӶ�ȷ������������������˳��д������lin
        }
        else if(in[i]!=pre[0])
        {
            rin[n2++] = in[i];//ȷ������������������˳��д������rin
        }
    }
    //���������������еĳ��ȵ����������еĳ���
    //��������������������ٺ�����,�������������� ���������������ĳ��ȶ��ǹ̶���
    //���� ��i=1��ʼ ��Ϊ��������ĵ�һ���Ǹ�
    for (i = 1;i < n;i++)
    {
        if (i< (n1+1))//n1�������������ĳ���
        {
            lpre[m1++] = pre[i];//��ǰ��˳����������ֵд������lpre
        }
        else
        {
            rpre[m2++] = pre[i];//��ǰ��˳����������ֵд������rpre
        }
    }
    node->lchild = createBiTree(lpre,lin,n1);//�ݹ����
    node->rchild = createBiTree(rpre,rin,n2);
    return node;
}

int main()
{
    char preNode[N];
    char inNode[N];
    int n1,n2;
    char ch='\0';
    BITree root=NULL;

    int flag=1;     //��־��״̬
    int opt=-1;     //ѡ�����
    while(1)
    {
        putchar('\n');
        printf("*****************�˵���*******************\n");
        if(flag==1)
        {
        printf("    1.����������������еݹ齨����\n");
        printf("    2.����������������зǵݹ齨����\n");
        printf("    0.�˳�\n");
        }
        if(flag==2)
        {
        printf("    3.����������ݹ飩\n");
        printf("    4.����������ݹ飩\n");
        printf("    5.����������ݹ飩\n");
        printf("    6.����������ǵݹ飩\n");
        printf("    7.����������ǵݹ飩\n");
        printf("    8.����������ǵݹ飩\n");
        printf("    9.�������\n");
        printf("    10.�ÿ���\n");
        printf("    0.�˳�\n");
        }
        printf("******************************************\n");

        printf("��������ţ�");
        scanf("%d",&opt);

        if(flag==1)
        {
            if( opt==1 || opt==2 )
            {
                fflush(stdin);
                n1 = 0;
                printf("�������������У�\n");
                while((ch = getchar())&&ch!='\n')
                    preNode[n1++] = ch;
                printf("�������������У�\n");
                n2 = 0;
                while((ch = getchar())&&ch!='\n')
                    inNode[n2++] = ch;
                preNode[n1]='\0';
                inNode[n2]='\0';
            }
            if(n1!=n2) exit(0);
            switch(opt)
            {
            case 1:
                root=createBiTree(preNode,inNode,n1);
                flag=2;
                cout<<"�����ɹ�"<<endl;
                LayerOrderBiTree(root);
                break;
            case 2:
                createBiTree2(root,preNode,inNode);
                flag=2;
                cout<<"�����ɹ�"<<endl;
                LayerOrderBiTree(root);
                break;
            case 0:
                exit(0);
            default:
                printf("������Ϸ���ţ�\n");
                break;
            }
        }
        else if(flag==2)
        {
            switch(opt)
            {
            case 3:
                preOrder(root);
                putchar('\n');
                break;
            case 4:
                inOrder(root);
                putchar('\n');
                break;
            case 5:
                postorder(root);
                putchar('\n');
                break;
            case 6:
                feipreorderTraverse(root);
                putchar('\n');
                break;
            case 7:
                feiinorderTraverse(root);
                putchar('\n');
                break;
            case 8:
                postTraverse(root);
                putchar('\n');
                break;
            case 9:
                LayerOrderBiTree(root);
                putchar('\n');
                break;
            case 10:
                Destory(root);
                flag=1;
                cout<<"���ÿ�!"<<endl;
                break;
            case 0:
                exit(0);
            default:
                printf("������Ϸ���ţ�\n");
                putchar('\n');
                break;
            }
        }
    }

    return 0;
}


