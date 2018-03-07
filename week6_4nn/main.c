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
    printf("������ѧԺ����n(n<=20)��������Ŀ����m(m<=20)��Ů����Ŀ����w(w<=20)�����Կո�ָ���\n");
    scanf("%d %d %d",&n,&m,&w);
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
int flag_name_acade=0;
void input_name_acade()
{
    int i;
    printf("��������ѧԺ���ƣ��س��ָ���\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",name_acad[i]);
    }
    flag_name_acade=1;
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
//�洢��Ŀ��ţ�ǰn��
int item_range[M+W][6]={0};
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
                item_range[i][j]=num;
            }
        }
        else if(flag==5)
        {
            for(j=0;j<5;j++)
            {
                printf("��%d��ѧԺ��ţ�\t",j+1);
                scanf("%d",&num);
                itac[i*soi+num-1]=s5[j];
                item_range[i][j]=num;
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
void sort_name_acade()
{
    int i,j,k;
    char copy_name_acid[N][10]={'0'};
    char scan_name_acid[10]={'0'};
    for(i=0;i<n;i++)//��������
    {
        strcpy(copy_name_acid[i],name_acad[i]);
    }
    printf("\nѧԺ����\t��Ŀ���\t�÷�\n");
    for(i=0;i<n;i++)
    {
        scan_name_acid[0]='~';
        for(j=0;j<n;j++)
        {
            if( strcmp(scan_name_acid,copy_name_acid[j])>0 )
            {
                strcpy(scan_name_acid,copy_name_acid[j]);
                k=j;
            }
        }
        for(j=0;j<soi;j++)
        {
            printf("%s\t\t%d\t\t%d\n",name_acad[k],j+1,itac[k*n+j]);
        }
        copy_name_acid[k][0]='~';
        putchar('\n');
    }

}

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
       ssoa[k]=-1;
    }
}

//������/Ů�������ܷ��������
void sort_sumofman(int key1,int key2)
{
    int ssom[N]={0};//sum score of man
    int i,j,k,temp=0;
    for(i=0;i<n;i++)
    {
        for(j=key1;j<m+key2;j++)
        {
            ssom[i]+= itac[j*n+i];
        }
    }
    if(key1){
        printf("����\tѧԺ���\tŮ���ܷ�\n");
    }
    else{
        printf("����\tѧԺ���\t�����ܷ�\n");
    }
    for(i=0;i<n;i++)
    {
        k=0;
        temp=0;
        for(j=0;j<n;j++)
        {
             if(temp<ssom[j])
             {
                 temp=ssom[j];
                 k=j;
             }
        }
       printf("%d\t\t%d\t\t%d\n",i+1,k+1,temp);
       ssom[k]=-1;
    }
}

//��ѧԺ��Ų�ѯѧԺĳ����Ŀ�����
void select_acad_item()
{
    int num_acad,num_item;
    printf("������ѧԺ��ţ���Ŀ��ţ��Կո�ָ�����\n");
    scanf("%d %d",&num_acad,&num_item);
    printf("�÷�Ϊ��\t%d\n",itac[(num_item-1)*n+(num_acad-1)]);
}

//����Ŀ��Ų�ѯȡ��ǰ������ǰ������ѧԺ
void select_range_item()
{
    int num_item,i ;
    printf("��������Ŀ��ţ�\t\n");
    scanf("%d",&num_item);
    printf("��Ŀ%d:\n",num_item);
    for(i=0;item_range[num_item-1][i]!=0;i++)
    {
        printf("��%d��Ϊ %d��ѧԺ\n",i+1,item_range[num_item-1][i]);
    }
}

//������ļ�
void output_file()
{
    FILE *fp;
    fp = fopen("D:\\compete_state.txt","w");
    if(fp==NULL)
    {
        printf("Failure to open compete_state.tet!\n");
        exit(0);
    }
    int i,j;
    fprintf(fp,"\nѧԺ���\t��Ŀ���\t�÷�\n");
    for(i=0;i<n;i++)
    {
        fputc('\n',fp);
        for(j=0;j<soi;j++)
        {
            fprintf(fp,"%d\t%d\t%d",i+1,j+1,itac[j*n+i]);
            fputc('\n',fp);
        }
    }

    fclose(fp);
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
        printf("\t2.����ѧԺ����(������ĸ������)\n");
        printf("\t3.������Ŀ����\n");
        printf("\t4.��ѧԺ������������\n");
        printf("\t5.��ѧԺ�������������\n");
        printf("\t6.��ѧԺ�ܷ����������\n");
        printf("\t7.�����������ܷ����������\n");
        printf("\t8.��Ů�������ܷ����������\n");
        printf("\t9.��ѧԺ��Ų�ѯѧԺĳ��Ŀ�����\n");
        printf("\t10.����Ŀ��Ų�ѯȡ��ǰ������ǰ������ѧԺ��\n");
        printf("\t11.���ݵ����ļ���\n");
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
            case 5:
                if(flag_name_acade)
                {
                    sort_name_acade();
                }
                else
                {
                    printf("��������ѧԺ���ƣ�\n");
                }
                break;
            case 6:
                sort_sumofacad();
                break;
            case 7:
                sort_sumofman(0,0);
                break;
            case 8:
                sort_sumofman(m,w);
                break;
            case 9:
                select_acad_item();
                break;
            case 10:
                select_range_item();
                break;
            case 11:
                output_file();
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
