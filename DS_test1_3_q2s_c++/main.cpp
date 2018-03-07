#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val;
    struct node* next;
};
typedef struct node* queue;

typedef struct AQUEUE
{
    queue front;
    queue rear;
}Que;

queue allocate_memory()
{
    queue p;
    p=(queue)malloc(sizeof(struct node));
    if(p==NULL)
    {
        printf("No enough memory to allocate!\n");
        exit(0);
    }
    p->next=NULL;
    return p;
}

void MakeNull(Que &Q)
{
    Q.front=allocate_memory();
    Q.front->next=NULL;
    Q.rear=Q.front;

}

int Empty(Que &Q)
{
    if(Q.front==Q.rear)
        return 1;
    else
        return 0;
}

int Front(Que &Q)
{
    return Q.front->next->val;
}

void EnQueue(int val,Que &Q)
{
    Q.rear->next=allocate_memory();
    Q.rear=Q.rear->next;
    Q.rear->val=val;
    Q.rear->next=NULL;
}

void DeQueue(Que &Q)
{
    queue temp;
    if(Empty(Q))
    {
        printf("The queue is empty!");
        return;
    }
    else
    {
        temp=Q.front->next;
        Q.front->next=temp->next;
        free(temp);
        if(Q.front->next==NULL)
            Q.rear=Q.front;
    }

}

//stack
void sMakeNull(Que &Q,Que &P)
{
    MakeNull(Q);
    MakeNull(P);
}

int sTop(Que &Q)
{
    if(!Empty(Q))
        return Q.rear->val;
    else
        return 0;
}

int sEmpty(Que &Q)
{
    if(!Empty(Q))
        return 1;
    return 0;
}

void sPush(int val,Que &Q)
{
    EnQueue(val,Q);
}

void sPop(Que &Q,Que &P)
{
    if(Empty(Q))
        return;
    while(Q.front->next->next!=NULL)
    {
        EnQueue(Front(Q),P);
        DeQueue(Q);
    }
    DeQueue(Q);
    while(!Empty(P))
    {
        EnQueue(Front(P),Q);
        DeQueue(P);
    }

}

void free_memory(Que &Q,Que &P)
{
    MakeNull(Q);
    MakeNull(P);

    free(Q.front);
    free(Q.rear);
    free(P.front);
    free(P.rear);
    printf("Free memory successfully!");
}


int main()
{
    Que Q;
    MakeNull(Q);
    Que P;//��������
    MakeNull(P);
    int len=0;

    while(1)
    {
        printf("\n************\n");
        printf("1.��ջ\n");
        printf("2.��ջ\n");
        printf("3.ջ��\n");
        printf("4.ջ��\n");
        printf("0.�˳�\n");
        printf("************\n");
        int n=-1;
        printf("��������ţ�");
        scanf("%d",&n);
        switch(n)
        {
        case 1:
            printf("��������ջֵ��");
            int val;
            scanf("%d",&val);
            sPush(val,Q);
            len++;
            break;
        case 2:
            if(Empty(Q))
            {
                printf("ջ�գ�\n");
                break;
            }
            sPop(Q,P);
            len--;
            printf("����ɳ�ջ��\n");
            break;
        case 3:
            if(Empty(Q))
            {
                printf("ջ�գ�\n");
                break;
            }
            printf("\nջ��ֵΪ��%d\n",sTop(Q));
            break;
        case 4:
            if(!len)
            {
                printf("ջ�գ�\n");
                break;
            }
            printf("\nջ��Ϊ��%d\n",len);
            break;
        case 0:
            if(!len) free_memory(Q,P);
            exit(0);
        default:
            printf("\n��������ȷ��ţ�\n");
            break;
        }
    }

    return 0;
}
