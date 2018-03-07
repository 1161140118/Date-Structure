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




