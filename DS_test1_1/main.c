#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 100


struct node
{
    double val;
    struct node * next;
    char c;
};

typedef struct node* Sstack;

//比较a（栈顶）与b（入栈）的优先级
char judege(char a, char b){
    int i,j;
    char jud[][7]={
    /*运算符之间的优先级制作成一张表格*/
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=','0'},
        {'>','>','>','>','0','>','>'},
        {'<','<','<','<','<','0','='}};
    switch(a){
        case '+': i=0; break;
        case '-': i=1; break;
        case '*': i=2; break;
        case '/': i=3; break;
        case '(': i=4; break;
        case ')': i=5; break;
        case '#': i=6; break;
    }
    switch(b){
        case '+': j=0; break;
        case '-': j=1; break;
        case '*': j=2; break;
        case '/': j=3; break;
        case '(': j=4; break;
        case ')': j=5; break;
        case '#': j=6; break;
    }
    return jud[i][j];
}

Sstack allocate_memory()
{
    Sstack p=NULL;
    p=(Sstack)malloc(sizeof(struct node));
    if(p==NULL)
    {
        printf("No enough memory to allocate!\n");
        exit(0);
    }
    p->next=NULL;
    return p;
}

//置空/初始化栈
Sstack MakeNull(Sstack S)
{
    if(S==NULL)
        S=allocate_memory();
    Sstack p=S,pr=S;
    while(p->next!=NULL)
    {
        pr=p;
        p=p->next;
        free(pr);
    }
    p->next=NULL;
    return S;
}

//压入数据
void Push_data(double val,Sstack S)
{
    Sstack p=NULL;
    p=allocate_memory();
    p->val=val;
    p->next=S->next;
    S->next=p;
}

//压入字符
void Push_c(char c,Sstack S)
{
    Sstack p=NULL;
    p=allocate_memory();
    p->c=c;
    p->next=S->next;
    S->next=p;
}

//弹出栈顶元素
void Pop(Sstack S)
{
    Sstack p;
    if(S->next!=NULL)
    {
        p=S->next;
        S->next=p->next;
        free(p);
    }
}

//取栈顶数据
double Top_data(Sstack S)
{
    if(S->next!=NULL)
        return S->next->val;
    else
        return ;
}

//取栈顶字符
char Top_c(Sstack S)
{
    if(S->next!=NULL)
        return S->next->c;
    else
        return '#';
}

//判断栈空
int Empty(Sstack S)
{
    if(S->next!=NULL)
        return 0;
    else
        return 1;
}

//Is the input a data?
int Isdata(char c)
{
    if((c>=48)&&(c<=57))
        return 1;
    return 0;
}
//Is the input a operator?
int Isoperate(char c)
{
    if((c>=40)&&(c<=47)&&(c!=44))
        return 1;
    return 0;
}

//后缀表达式字符串
char expre[N];
//后缀表达式字符编号
int cnt_exp=0;

//输入信息
void Input(Sstack DA,Sstack OP)
{
    char c='\0';
    int flag_bracket=0;
    int legal_bracket=0;
    while((c=getchar())!='\n')
    {
        if(Isdata(c))
        {
            printf("%c",c);
            expre[cnt_exp++]=c;
        }
        else if(c=='.')
        {
            printf("%c",c);
            expre[cnt_exp++]=c;
        }
        else if(Isoperate(c))
        {
            expre[cnt_exp++]=' ';
            putchar(' ');

            if(c=='(') legal_bracket++;
            if(c==')') legal_bracket--;

            flag_bracket=0;
            while(judege(Top_c(OP),c)=='>')
            {
                if((c!='('||flag_bracket)&&Top_c(OP)!='(')
                {
                    printf("%c",Top_c(OP));
                    expre[cnt_exp++]=Top_c(OP);
                }
                Pop(OP);
                flag_bracket=1;
            }
            if(judege(Top_c(OP),c)=='=')
            {
                Pop(OP);
                continue;
            }
            if(c!=')')
                Push_c(c,OP);
        }
    }
    if(legal_bracket)
    {
        printf("\nIllegal input!");
        exit(0);
    }
    while(Top_c(OP)!='#')
    {
        if(Top_c(OP)=='('||Top_c(OP)==')') continue;
        printf(" %c",Top_c(OP));
        expre[cnt_exp++]=' ';
        expre[cnt_exp++]=Top_c(OP);
        Pop(OP);
    }
}
//计算表达式
double work(Sstack DA)
{
    int i=0,flag_double=0;  //flag_double:小数
    double a=0,b=0,dou=0;//dou:处理小数
    char c;
    while((c=expre[i++])!='#')
    {
        if(Isdata(c))
        {
            dou=(double)(c-48);
            double cnt_double=0;
            flag_double=0;
            while((c=expre[i++])!=' ')
            {
                if(c!='.')
                    dou = dou*10+c-48;
                if(c=='.') flag_double=1;
                if(flag_double) cnt_double++;
            }
            if(cnt_double)
                dou=dou/pow(10,cnt_double-1);
            Push_data(dou,DA);
        }
        else if(c==' ')
            continue;
        else
        {
            a=Top_data(DA);
            Pop(DA);
            b=Top_data(DA);
            if(Empty(DA))   //第一位为负号
            {
                b=0;
            }
            else Pop(DA);
            switch(c)
            {
                case '+':Push_data(a+b,DA);break;
                case '-':Push_data(b-a,DA);break;
                case '*':Push_data(a*b,DA);break;
                case '/':
                    if(a!=0)
                    {
                        Push_data(b/a,DA);break;
                    }
                    printf("\n error:The divisor is 0!\n");
                    exit(0);

            }
        }
    }
    return Top_data(DA);
}



int main()
{


    char con='\0';
    printf("\n***** Press enter to calculate!");

    while((con=getchar())=='\n')
    {
        printf("Input,please!\n");
        Sstack OP=NULL;         //存储运算符（不输出）
        Sstack DA=NULL;         //存储数据

        OP=MakeNull(OP);
        DA=MakeNull(DA);
        //初始化后缀表达式
        cnt_exp=0;
        int i;
        for(i=0;i<N-1;i++)  expre[i]='#';

        Input(DA,OP);
        //putchar('\n');
        //for(i=0;expre[i]!='#';i++)  printf("%c",expre[i]);

        printf("\n%lf",work(DA));
        putchar('\n');
        printf("\n***** Press enter to calculate!");
        fflush(stdin);
        MakeNull(OP);
        free(OP);
        MakeNull(DA);
        free(DA);
    }



    return 0;
}
