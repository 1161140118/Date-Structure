#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val;
    struct node* next;
};
typedef struct node* stack;

stack allocate_memory()
{
    stack p;
    p=(stack)malloc(sizeof(struct node));
    if(p==NULL)
    {
        printf("No enough memory to allocate!\n");
        exit(0);
    }
    p->next=NULL;
    return p;
}

stack MakeNull(stack S)
{
    if(S==NULL)
        S=allocate_memory();
    S->next=NULL;
    return S;
}

void Push(int val,stack S)
{
    stack p=NULL;
    p=allocate_memory();
    p->val=val;
    p->next=S->next;
    S->next=p;
}

void Pop(stack S)
{
    stack p;
    if(S->next!=NULL)
    {
        p=S->next;
        S->next=p->next;
        free(p);
    }
}

int Top(stack S)
{
    return S->next->val;
}

int Empty(stack S)
{
    if(S->next!=NULL)
        return 0;
    else
        return 1;
}

//queue
void qMakeNull(stack Front,stack Rear)
{
    MakeNull(Front);
    MakeNull(Rear);
}

int qEmpty(stack Front,stack Rear)
{
    if(Front->next==NULL&&Rear->next==NULL)
        return 1;
    return 0;
}

int qFront(stack Front,stack Rear)
{
    if(Front->next==NULL)
    {
        while(Rear->next!=NULL)
        {
            Push(Top(Rear),Front);
            Pop(Rear);
        }
    }
    if(Front->next!=NULL)
        return Top(Front);
    else
    {
        printf("The queue is empty!\n");
        return;
    }
}

void EnQueue(int val,stack Rear)
{
    Push(val,Rear);
}

void DeQueue(stack Front,stack Rear)
{
    if(qEmpty(Front,Rear))
        return;
    if(Front->next!=NULL)
    {
        Pop(Front);
        return;
    }
    while(Rear->next->next!=NULL)
    {
        Push(Top(Rear),Front);
        Pop(Rear);
    }
}

void free_memory(stack Front,stack Rear)
{
    if(!qEmpty(Front,Rear))
    {
        MakeNull(Front);
        free(Front);
        MakeNull(Rear);
        free(Rear);
    }
    printf("The memory has been released!");
}

int main()
{
    stack Front=NULL;
    stack Rear=NULL;
    Front=MakeNull(Front);
    Rear=MakeNull(Rear);
    int len=0;

    while(1)
    {
        printf("\n************\n");
        printf("1.入队\n");
        printf("2.出队\n");
        printf("3.队首\n");
        printf("4.队长\n");
        printf("0.退出\n");
        printf("************\n");
        int n=-1;
        printf("请输入序号：");
        scanf("%d",&n);
        switch(n)
        {
        case 1:
            printf("请输入入队值：");
            int val;
            scanf("%d",&val);
            EnQueue(val,Rear);
            len++;
            break;
        case 2:
            if(qEmpty(Front,Rear))
            {
                printf("队空！\n");
                break;
            }
            DeQueue(Front,Rear);
            len--;
            printf("已完成出队！\n");
            break;
        case 3:
            if(qEmpty(Front,Rear))
            {
                printf("队空！\n");
                break;
            }
            printf("\n队首值为：%d\n",qFront(Front,Rear));
            break;
        case 4:
            if(!len)
            {
                printf("队空！\n");
                break;
            }
            printf("\n队长为：%d\n",len);
            break;
        case 0:
            free_memory(Front,Rear);
            exit(0);
        default:
            printf("\n请输入正确序号！\n");
            break;
        }
    }


    return 0;
}
