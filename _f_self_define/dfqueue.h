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

queue allocate_memory();
void MakeNull(Que &Q);
int Empty(Que &Q);
void EnQueue(int val,Que &Q);
void DeQueue(Que &Q);
