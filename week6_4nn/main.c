#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
#define M 20
#define W 20
//输入基本数据
int n,m,w,soi;//sum of item = m+w

//（项目，学院）数组
int *itac=NULL;

void nmwinput()
{
    printf("请输入学院总数n(n<=20)，男子项目总数m(m<=20)，女子项目总数w(w<=20)：（以空格分隔）\n");
    scanf("%d %d %d",&n,&m,&w);
    if(n>N||m>M||w>W)
    {
        printf("Input error！");
        exit(1);
    }
    soi=m+w;
    //（项目，学院）数组 初始化
    itac = (int *)calloc(n*(soi),sizeof(int));
    if(itac==NULL)
    {
    printf("No enough memory!\n");
    exit(1);
    }
}

//赋分数组
int s3[3]={5,3,2};
int s5[5]={7,5,3,2,1};

//定义学院/项目名称
char name_acad[N][10]={"\0"};
char name_item[M+N][10]={"\0"};

//存储学院/项目名称
int flag_name_acade=0;
void input_name_acade()
{
    int i;
    printf("依次输入学院名称（回车分隔）\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",name_acad[i]);
    }
    flag_name_acade=1;
}
void input_name_item()
{
    int i;
    printf("依次输入项目名称（回车分隔）\n");
    for(i=0;i<soi;i++)
    {
        scanf("%s",name_item[i]);
    }
}
//存储项目编号：前n名
int item_range[M+W][6]={0};
//存储分数
void input_score()
{
    int i,j,num,flag=0;//项目编号i，学院编号j

    for(i=0;i<m+w;i++)
    {
        printf("\n第%d个项目,取前三名请输入3，取前五名请输入5：\t",i+1);
        scanf("%d",&flag);
        if(flag==3)
        {
            for(j=0;j<3;j++)
            {
                printf("第%d名学院编号：\t",j+1);
                scanf("%d",&num);
                itac[i*soi+num-1]=s3[j];
                item_range[i][j]=num;
            }
        }
        else if(flag==5)
        {
            for(j=0;j<5;j++)
            {
                printf("第%d名学院编号：\t",j+1);
                scanf("%d",&num);
                itac[i*soi+num-1]=s5[j];
                item_range[i][j]=num;
            }
        }
        else i--;
    }
}

//按学院编号排序输出
void sort_acad()
{
    int i,j;
    printf("\n学院编号\t项目编号\t得分\n");
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

//按学院名称排序输出
void sort_name_acade()
{
    int i,j,k;
    char copy_name_acid[N][10]={'0'};
    char scan_name_acid[10]={'0'};
    for(i=0;i<n;i++)//复制名单
    {
        strcpy(copy_name_acid[i],name_acad[i]);
    }
    printf("\n学院名称\t项目编号\t得分\n");
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

//按学院总分排序输出
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
    printf("名次\t学院编号\t总分\n");
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

//按男子/女子团体总分排序输出
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
        printf("名次\t学院编号\t女子总分\n");
    }
    else{
        printf("名次\t学院编号\t男子总分\n");
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

//按学院编号查询学院某个项目的情况
void select_acad_item()
{
    int num_acad,num_item;
    printf("请输入学院编号，项目编号（以空格分隔）：\n");
    scanf("%d %d",&num_acad,&num_item);
    printf("得分为：\t%d\n",itac[(num_item-1)*n+(num_acad-1)]);
}

//按项目编号查询取得前三名或前五名的学院
void select_range_item()
{
    int num_item,i ;
    printf("请输入项目编号：\t\n");
    scanf("%d",&num_item);
    printf("项目%d:\n",num_item);
    for(i=0;item_range[num_item-1][i]!=0;i++)
    {
        printf("第%d名为 %d号学院\n",i+1,item_range[num_item-1][i]);
    }
}

//输出到文件
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
    fprintf(fp,"\n学院编号\t项目编号\t得分\n");
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

    //菜单
    while(1)
    {
        printf("\n\t*****菜单*****：\n");
        printf("\t1.开始输入各项目前三名或前五名的成绩；\n");
        printf("\t2.输入学院名称(仅含字母和数字)\n");
        printf("\t3.输入项目名称\n");
        printf("\t4.按学院编号排序输出；\n");
        printf("\t5.按学院名称排序输出；\n");
        printf("\t6.按学院总分排序输出；\n");
        printf("\t7.按男子团体总分排序输出；\n");
        printf("\t8.按女子团体总分排序输出；\n");
        printf("\t9.按学院编号查询学院某项目情况；\n");
        printf("\t10.按项目编号查询取得前三名或前五名的学院；\n");
        printf("\t11.数据导出文件；\n");
        printf("\t0.退出。\n");
        printf("请输入序号：\n");
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
                    printf("请先输入学院名称！\n");
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
                printf("请输入菜单所给序号！\n");
                continue;



        }
    }

    return 0;
}
