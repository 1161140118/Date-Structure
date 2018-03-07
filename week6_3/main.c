#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//记录胜负关系
void input(int *a,int n)
{
    int i,j;
    printf("请输入对局胜负，胜为1，负为0：\n");
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            printf("对局：%d vs %d 结果：",i+1,j+1);
            scanf("%d",&a[j*n+i]);
        }
    }
}

void visit(int *ved,int *trace,int *a,int n)
{
    int i=0,j=0,k=0,flag=0;
    trace[0]=1;//第一个值设为1
    for(i=1;i<n;i++)//从第二个数开始，扫描后面的数
    {
        flag=0;
        for(j=i-1;j>=0;j--)//从trace尾值开始，向前扫描
        {
            if(a[i*n+trace[j]-1])//如果i vs trace[j]为1 则在其后插入i+1
            {
                for(k=i-1;k>j;k--)
                {
                    trace[k+1]=trace[k];
                }
                trace[j+1]=i+1;
                flag=1;//标志 找到插入点
                break;
            }
        }
        if(!flag)//如果没有1
        {
            for(k=i-1;k>=0;k--)
            {
                trace[k+1]=trace[k];
            }
            trace[j+1]=i+1;
        }
    }
}

int main()
{
//统计胜负信息
    int n ,i;
    printf("请输入选手总数:\n");
    scanf("%d",&n);

    int *a=NULL;
    a=(int *)calloc(n*n,sizeof(int));
    if(a==NULL)
    {
        printf("No enough memory!\n");
        exit(1);
    }
    input(a,n);

//遍历
    //visited数组 记录各点是否经过
    int *ved=NULL;
    ved=(int *)calloc(n,sizeof(int));
    if(ved==NULL)
    {
        printf("No enough memory!\n");
        exit(1);
    }
    //路径上的点 如 1 3 5 2 ……
    int *trace=NULL;
    trace=(int *)calloc(n,sizeof(int));
    if(trace==NULL)
    {
        printf("No enough memory!\n");
        exit(1);
    }

    visit(ved,trace,a,n);

//输入序列
    printf("序列为：");
    for(i=0;i<n;i++)
    {
        printf("%d\t",trace[i]);
    }

    free(ved);
    free(trace);
    free(a);
    return 0;
}
