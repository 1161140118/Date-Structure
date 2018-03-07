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
//����������
int n=0;
//�����������
position InsertByOrder(position l)
{
    position p=NULL,pr=l,temp=NULL;
    p=(position)malloc(sizeof(list));
    if(p==NULL)
    {
        printf("No enough memory to allocate!\n");
        exit(0);
    }

    //�½ڵ���Ϣ
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
        while(pr!=NULL&&(p->price)>=(pr->price))//���ҺϷ�λ��
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

//��ʾ��Ϣ
void show(position l)
{
    int i=1;
    position pr=l;
    printf("���\t�ҵ�����\tƷ��\t\t����\t\t����\n");
    while(pr!=NULL)
    {
        printf("%d\t%-12s\t%-12s\t%.2f\t\t%d\n",i,pr->name,pr->brand,pr->price,pr->amount);
        pr=pr->next;
        i++;
    }
}

//ɾ���ڵ�
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
        printf("��������ȷ��ţ�\n");

    return l;
}
//���½ڵ�
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
//���»�ɾ������
position update_data(position l)
{
    int num,choose=0;
    printf("��������»�ɾ����Ŀ��ţ�\n");
    scanf("%d",&num);
    while(choose==0)
    {
        printf("1������\n");
        printf("2��ɾ��\n");
        printf("��ѡ��");
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
            printf("\n��������ȷ��ţ�\n");
            choose=0;
            break;
        }
    }

    return l;
}
//��ѯ��Ϣ
void Searchdata(position l)
{
    if(l==NULL)
    {
        printf("ϵͳ���������ݣ�\n");
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
                printf("%d\t��Ʒ���ƣ�%-12s\tƷ�ƣ�%-12s\t�۸�%.2f\t������%d\n",i+1,pr->name,pr->brand,pr->price,pr->amount);
                f1=1;
           }
        pr=pr->next;
    }
    if(!f1)
        printf("δ�ҵ������Ϣ��\n");
}
//�ͷ��ڴ�
position DeleteMemory(position l)
{
    if(l==NULL)
    {
        printf("������Ϣ!\n");
        return l;
    }
    position pr=l,temp=NULL;
    while(pr!=NULL)
    {
        temp=pr;
        pr=pr->next;
        free(temp);
        n--;
        printf("ʣ��%d��\n",n);
    }
    l=NULL;
    printf("�ڴ��ͷ���ϣ�\n");
    return l;
}

//�������������
void output_bin(position l)
{
    int i;
    position pr=l;
    if(l==NULL)
    {
        printf("������Ϣ��\n");
        return;
    }
    FILE *fp;
    if((fp=fopen("F:\\week7_1.bin","wb"))==NULL)
    {
        printf("Failure to open txt!\n");
        return;
    }
    fputc(n,fp);                                //��Ϣ������
    for(i=0;i<n;i++)
    {
        fwrite(pr,sizeof(list),1,fp);
        pr=pr->next;                            //ָ����һ���ṹ��
    }
    fclose(fp);
}
//�����ƶ�������
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
    n=fgetc(fp);                                //��Ϣ������
    for(i=0;i<n;i++)
    {
        p=(position)malloc(sizeof(list));
        if(p==NULL)
        {
            printf("No enough memory to allocate!\n");
            exit(0);
        }
        //�½ڵ���Ϣ
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
    printf("������ɣ�\n");
    return l;
}

int main()
{
    int num;
    char flag;
    position l=NULL;//l Ϊ��������ͬʱΪ�׵�ַ

    while(1)
    {
        printf("\n*******************�˵�***********************��\n");
        printf("\t1��Ӫҵ��ʼ�������ļ��ָ��������ݣ���\n");
        printf("\t2���������������ݣ���\n");
        printf("\t3����������»�ɾ������\n");
        printf("\t4����ѯ��Ϣ��\n");
        printf("\t5����ʾȫ����Ϣ��\n");
        printf("\t6��������Ϣ��\n");
        printf("\t7��Ӫҵ�������������ݴ����ļ�����\n");
        printf("\t0���˳���\n");
        printf("**********************************************\n");
        printf("������˵����...\n");
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
                    printf("�����ظ����룡\n");
                break;
            case 2:
                flag='y';
                while(flag!='\n')
                {
                    l=InsertByOrder(l);
                    printf("������������س�������");
                    fflush(stdin);
                    flag=getchar();
                }
                break;
            case 3:
                if(l==NULL)
                    printf("������Ϣ��\n");
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
                    printf("������Ϣ��\n");
                else
                    show(l);
                break;
            case 6:
                flag='y';
                printf("���½�ɾ��������Ϣ�����س���ȷ����");
                fflush(stdin);
                flag=getchar();
                if(flag!='\n')
                    printf("��ȡ����\n");
                else
                    l=DeleteMemory(l);
                break;
            case 7:
                output_bin(l);
                break;
            default:
                printf("������˵���ţ�\n");
                break;
        }
    }
    return 0;
}
