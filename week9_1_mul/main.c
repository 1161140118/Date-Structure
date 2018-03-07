#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    double coef;
    int exp;
    struct list * next;
}polynode;
typedef struct list* polypointer;

//申请空间
polypointer allocate_memory()
{
    polypointer p=NULL;
    p=(polypointer)malloc(sizeof(polynode));
    if(p==NULL)
    {
        printf("No enough memory to allocate!\n");
        exit(0);
    }
    return p;
}

//新建节点
polypointer attach_poly()
{
    polypointer p=allocate_memory();
    fflush(stdin);
    putchar('\n');
    printf("Input the coef:");
    scanf("%lf",&p->coef);
    printf("Input the exp :");
    scanf("%d",&p->exp);
    p->next=NULL;
    return p;
}

//新建多项式
polypointer new_poly()
{
    polypointer p=NULL,pn=NULL;
    p=attach_poly();
    pn=p;
    while(pn->coef!=0)
    {
        pn->next=attach_poly();
        pn=pn->next;
    }
    return p;
}

//显示多项式
void show_poly(polypointer p)
{
    putchar('\n');
    printf("coef:\t    exp:\n");
    while(p!=NULL)
    {
        if(p->coef!=0)
            printf("%lf\t%d\t\n",p->coef,p->exp);
        p=p->next;
    }
}

//计算并显示乘积
polypointer mul_poly(polypointer P,polypointer M)
{
    polypointer S=NULL,pp=P,pm=M,ps=NULL,pn=NULL;
    double s_coef=0;
    int s_exp=0;
    S=allocate_memory();
    ps=S;
    ps->coef=0;
    ps->exp=0;
    ps->next=allocate_memory();
    ps->next->coef=0;
    ps->next->exp=0;
    ps->next->next=NULL;

    while(pp->next!=NULL)
    {
        while(pm->next!=NULL)
        {
            s_coef=pp->coef*pm->coef;
            s_exp=pp->exp+pm->exp;
            while(1)
            {
                if((s_exp!=ps->exp)&&(s_exp<=(ps->next->exp)))
                    ps=ps->next;
                else if(s_exp==ps->exp)
                 {
                     ps->coef+=s_coef;
                     ps=ps->next;
                     break;
                 }
                else
                {
                    pn=ps->next;
                    ps->next=allocate_memory();
                    ps->next->coef=s_coef;
                    ps->next->exp=s_exp;
                    ps->next->next=pn;
                    break;
                }
            }
            pm=pm->next;
        }
        pp=pp->next;
        pm=M;
        ps=S;
    }
    return S;
}

//释放内存
void free_poly(polypointer p)
{
    polypointer pn=NULL;
    while(p->next!=NULL)
    {
        pn=p;
        p=p->next;
        free(pn);
    }
}

int main()
{
    polypointer P=NULL;
    polypointer M=NULL;
    polypointer S=NULL;
    printf("Input poly P by the descending power\n");
    P=new_poly();
    show_poly(P);
    printf("Input poly M by the descending power\n");
    M=new_poly();
    show_poly(M);
    putchar('\n');
    printf("The product of P and M is:\n");
    S=mul_poly(P,M);
    show_poly(S);

    free_poly(P);
    free_poly(M);
    free_poly(S);

    return 0;
}
