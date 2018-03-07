#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
#define M 20
#define W 20
//�����������
int n,m,w,soi;//sum of item = m+w

//����Ŀ��ѧԺ������
int *itac=NULL;

void nmwinput()
{
    printf("������ѧԺ����n(n<=20)��������Ŀ����m(m<=20)��Ů����Ŀ����w(w<=20)�����Զ��ŷָ���\n");
    scanf("%d,%d,%d",&n,&m,&w);
    if(n>N||m>M||w>W)
    {
        printf("Input error��");
        exit(1);
    }
    soi=m+w;
    //����Ŀ��ѧԺ������ ��ʼ��
    itac = (int *)calloc(n*(soi),sizeof(int));
    if(itac==NULL)
    {
    printf("No enough memory!\n");
    exit(1);
    }
}

//��������
int s3[3]={5,3,2};
int s5[5]={7,5,3,2,1};

//����ѧԺ/��Ŀ����
char name_acad[N][10]={"\0"};
char name_item[M+N][10]={"\0"};
//�洢ѧԺ/��Ŀ����
void input_name_acade()
{
    int i;
    printf("��������ѧԺ���ƣ��س��ָ���\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",name_acad[i]);
    }

}
void input_name_item()
{
    int i;
    printf("����������Ŀ���ƣ��س��ָ���\n");
    for(i=0;i<soi;i++)
    {
        scanf("%s",name_item[i]);
    }
}
//�洢����
void input_score()
{
    int i,j,num,flag=0;//��Ŀ���i��ѧԺ���j

    for(i=0;i<m+w;i++)
    {
        printf("\n��%d����Ŀ,ȡǰ����������3��ȡǰ����������5��\t",i+1);
        scanf("%d",&flag);
        if(flag==3)
        {
            for(j=0;j<3;j++)
            {
                printf("��%d��ѧԺ��ţ�\t",j+1);
                scanf("%d",&num);
                itac[i*soi+num-1]=s3[j];
            }
        }
        else if(flag==5)
        {
            for(j=0;j<5;j++)
            {
                printf("��%d��ѧԺ��ţ�\t",j+1);
                scanf("%d",&num);
                itac[i*soi+num-1]=s5[j];
            }
        }
        else i--;
    }
}
//��ѧԺ����������
void sort_acad()
{
    int i,j;
    printf("\nѧԺ���\t��Ŀ���\t�÷�\n");
    for(i=0;i<n;i++)
    {
        putchar('\n');
        for(j=0;j<soi;j++)
        {
            printf("%d\t\t%d\t\t%d",i+1,j+1,itac[j*n+i]);
            putchar('\n');
        }
    }
}
//��ѧԺ�����������

//��ѧԺ�ܷ��������
void sort_sumofacad()
{
    int ssoa[N]={0};//sum score of academy
    int i,j,k,temp=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<soi;j++)
        {
            ssoa[i]+= itac[j*n+i];
        }
    }
    printf("����\tѧԺ���\t�ܷ�\n");
    for(i=0;i<n;i++)
    {
        k=0;
        temp=0;
        for(j=0;j<n;j++)
        {
             if(temp<ssoa[j])
             {
                 temp=ssoa[j];
                 k=j;
             }
        }
       printf("%d\t\t%d\t\t%d\n",i+1,k+1,temp);
       ssoa[k-1]=-1;
    }
}


int main()
{
    int num;
    nmwinput();

    //�˵�
    while(1)
    {
        printf("\n\t*****�˵�*****��\n");
        printf("\t1.��ʼ�������Ŀǰ������ǰ�����ĳɼ���\n");
        printf("\t2.����ѧԺ����\n");
        printf("\t3.������Ŀ����\n");
        printf("\t4.��ѧԺ������������\n");
        printf("\t5.��ѧԺ�������������\n");
        printf("\t6.��ѧԺ�ܷ����������\n");
        printf("\t7.����Ů�����ܷ����������\n");
        printf("\t8.��ѧԺ��Ų�ѯѧԺĳ��Ŀ�����\n");
        printf("\t9.����Ŀ��Ų�ѯȡ��ǰ������ǰ������ѧԺ��\n");
        printf("\t10.���ݵ����ļ���\n");
        printf("\t0.�˳���\n");
        printf("��������ţ�\n");
        scanf("%d",&num);

        switch(num)
        {
            case 1:
                input_score();
                break;
            case 2:
                input_name_acade();
                break;
            case 3:
                input_name_item();
                break;
            case 4:
                sort_acad();
                break;
            case 6:
                sort_sumofacad();
                break;
            case 7:

                break;

            case 0:
                exit(0);
            default:
                printf("������˵�������ţ�\n");
                continue;



        }
    }

    return 0;
}
