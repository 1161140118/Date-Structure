#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 10

struct link
{
    double price;
    struct link* next;
    int amount;
    char name[L];
    char brand[L];
};
typedef  struct link list;
typedef  struct link *position;

char *limit_gets(char *str)
{
    gets(str);
    str[L-1]='\0';
    return str;
}
//数据总条数
int n=0;
//升序插入数据
position InsertByOrder(position l)
{
    position p=NULL,pr=l,temp=NULL;
    p=(position)malloc(sizeof(list));
    if(p==NULL)
    {
        printf("No enough memory to allocate!\n");
        exit(0);
    }

    //新节点信息
    fflush(stdin);
    printf("Input name(within 8 characters):");
    limit_gets(p->name);
    fflush(stdin);
    printf("Input brand(within 8 characters):");
    limit_gets(p->brand);
    fflush(stdin);
    printf("Input price:");
    scanf("%lf",&p->price);
    printf("Input amount:");
    scanf("%d",&p->amount);
    p->next=NULL;

    if(pr==NULL)
    {
        l=p;
    }
    else
    {
        while(pr!=NULL&&(p->price)>=(pr->price))//查找合法位置
        {
            temp=pr;
            pr=pr->next;
        }
        if(temp==NULL)
        {
            l=p;
            p->next=pr;
        }
        else
        {
            temp->next=p;
            p->next=pr;
        }
    }
    n++;
    return l;
}

//显示信息
void show(position l)
{
    int i=1;
    position pr=l;
    printf("序号\t家电名称\t品牌\t\t单价\t\t数量\n");
    while(pr!=NULL)
    {
        printf("%d\t%-12s\t%-12s\t%.2f\t\t%d\n",i,pr->name,pr->brand,pr->price,pr->amount);
        pr=pr->next;
        i++;
    }
}

//删除节点
position Delete_note(position l,int num)
{
    int i;
    position pr=l,temp=l;

    if(num>=1&&num<=n)
    {
        for(i=1;i<num;i++)
        {
            temp=pr;
            pr=pr->next;
        }
        if(pr==l)
        {
            l=pr->next;
        }
        else
        {
            temp->next=pr->next;
        }
        free(pr);
        n--;
    }
    else
        printf("请输入正确序号！\n");

    return l;
}
//更新节点
position update_node(position l,int num)
{
    position pr=l;
    int i;
    for(i=1;i<num;i++)
    {
        pr=pr->next;
    }
    printf("Input new price:");
    scanf("%lf",&pr->price);
    printf("Input new amount:");
    scanf("%d",&pr->amount);
    if(pr->amount<=0)
        l=Delete_note(l,num);
    return l;
}
//更新或删除数据
position update_data(position l)
{
    int num,choose=0;
    printf("请输入更新或删除项目序号：\n");
    scanf("%d",&num);
    while(choose==0)
    {
        printf("1、更新\n");
        printf("2、删除\n");
        printf("请选择：");
        scanf("%d",&choose);
        switch(choose)
        {
        case 1:
            l=update_node(l,num);
            break;
        case 2:
            l=Delete_note(l,num);
            break;
        default:
            printf("\n请输入正确序号！\n");
            choose=0;
            break;
        }
    }

    return l;
}
//查询信息
void Searchdata(position l)
{
    if(l==NULL)
    {
        printf("系统中暂无数据！\n");
        return ;
    }
    int i,f1=0;
    position pr=l;
    list New;
    New.next=NULL;
    fflush(stdin);
    printf("Input name(within 8 characters):");
    limit_gets(New.name);
    fflush(stdin);
    printf("Input brand(within 8 characters):");
    limit_gets(New.brand);
    fflush(stdin);
    putchar('\n');
    for(i=0;i<n;i++)
    {
        if(!(strcmp(pr->name,New.name)||strcmp(pr->brand,New.brand)))
           {
                printf("%d\t商品名称：%-12s\t品牌：%-12s\t价格：%.2f\t数量：%d\n",i+1,pr->name,pr->brand,pr->price,pr->amount);
                f1=1;
           }
        pr=pr->next;
    }
    if(!f1)
        printf("未找到相关信息！\n");
}
//释放内存
position DeleteMemory(position l)
{
    if(l==NULL)
    {
        printf("暂无信息!\n");
        return l;
    }
    position pr=l,temp=NULL;
    while(pr!=NULL)
    {
        temp=pr;
        pr=pr->next;
        free(temp);
        n--;
        printf("剩余%d条\n",n);
    }
    l=NULL;
    printf("内存释放完毕！\n");
    return l;
}

//二进制输出数据
void output_bin(position l)
{
    int i;
    position pr=l;
    if(l==NULL)
    {
        printf("暂无信息！\n");
        return;
    }
    FILE *fp;
    if((fp=fopen("F:\\week7_1.bin","wb"))==NULL)
    {
        printf("Failure to open txt!\n");
        return;
    }
    fputc(n,fp);                                //信息总条数
    for(i=0;i<n;i++)
    {
        fwrite(pr,sizeof(list),1,fp);
        pr=pr->next;                            //指向下一个结构体
    }
    fclose(fp);
}
//二进制读入数据
position input_bin(position l)
{
    int i;
    FILE *fp;
    if((fp=fopen("F:\\week7_1.bin","rb"))==NULL)
    {
        printf("Failure to open txt!\n");
        return NULL;
    }

    position p=NULL,pr=l;
    n=fgetc(fp);                                //信息总条数
    for(i=0;i<n;i++)
    {
        p=(position)malloc(sizeof(list));
        if(p==NULL)
        {
            printf("No enough memory to allocate!\n");
            exit(0);
        }
        //新节点信息
        fread(p,sizeof(list),1,fp);
        p->next=NULL;

        if(pr==NULL)
        {
            pr=p;
            l=pr;
        }
        else
        {
            pr->next=p;
            pr=p;
        }
    }
    printf("导入完成！\n");
    return l;
}

int main()
{
    int num;
    char flag;
    position l=NULL;//l 为链表名，同时为首地址

    while(1)
    {
        printf("\n*******************菜单***********************：\n");
        printf("\t1、营业开始（读入文件恢复链表数据）；\n");
        printf("\t2、进货（插入数据）；\n");
        printf("\t3、提货（更新或删除）；\n");
        printf("\t4、查询信息；\n");
        printf("\t5、显示全部信息；\n");
        printf("\t6、更新信息；\n");
        printf("\t7、营业结束（链表数据存入文件）；\n");
        printf("\t0、退出。\n");
        printf("**********************************************\n");
        printf("请输入菜单编号...\n");
        fflush(stdin);
        scanf("%d",&num);
        putchar('\n');
        switch(num)
        {
            case 0:
                l=DeleteMemory(l);
                exit(0);
                break;
            case 1:
                if(!n)
                    l=input_bin(l);
                else
                    printf("请勿重复导入！\n");
                break;
            case 2:
                flag='y';
                while(flag!='\n')
                {
                    l=InsertByOrder(l);
                    printf("任意键继续，回车结束：");
                    fflush(stdin);
                    flag=getchar();
                }
                break;
            case 3:
                if(l==NULL)
                    printf("暂无信息！\n");
                else
                {
                    show(l);
                    l=update_data(l);
                }
                break;
            case 4:
                Searchdata(l);
                break;
            case 5:
                if(l==NULL)
                    printf("暂无信息！\n");
                else
                    show(l);
                break;
            case 6:
                flag='y';
                printf("更新将删除现有信息，按回车键确定：");
                fflush(stdin);
                flag=getchar();
                if(flag!='\n')
                    printf("已取消！\n");
                else
                    l=DeleteMemory(l);
                break;
            case 7:
                output_bin(l);
                break;
            default:
                printf("请输入菜单编号！\n");
                break;
        }
    }
    return 0;
}
