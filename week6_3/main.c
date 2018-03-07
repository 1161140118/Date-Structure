#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//��¼ʤ����ϵ
void input(int *a,int n)
{
    int i,j;
    printf("������Ծ�ʤ����ʤΪ1����Ϊ0��\n");
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            printf("�Ծ֣�%d vs %d �����",i+1,j+1);
            scanf("%d",&a[j*n+i]);
        }
    }
}

void visit(int *ved,int *trace,int *a,int n)
{
    int i=0,j=0,k=0,flag=0;
    trace[0]=1;//��һ��ֵ��Ϊ1
    for(i=1;i<n;i++)//�ӵڶ�������ʼ��ɨ��������
    {
        flag=0;
        for(j=i-1;j>=0;j--)//��traceβֵ��ʼ����ǰɨ��
        {
            if(a[i*n+trace[j]-1])//���i vs trace[j]Ϊ1 ����������i+1
            {
                for(k=i-1;k>j;k--)
                {
                    trace[k+1]=trace[k];
                }
                trace[j+1]=i+1;
                flag=1;//��־ �ҵ������
                break;
            }
        }
        if(!flag)//���û��1
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
//ͳ��ʤ����Ϣ
    int n ,i;
    printf("������ѡ������:\n");
    scanf("%d",&n);

    int *a=NULL;
    a=(int *)calloc(n*n,sizeof(int));
    if(a==NULL)
    {
        printf("No enough memory!\n");
        exit(1);
    }
    input(a,n);

//����
    //visited���� ��¼�����Ƿ񾭹�
    int *ved=NULL;
    ved=(int *)calloc(n,sizeof(int));
    if(ved==NULL)
    {
        printf("No enough memory!\n");
        exit(1);
    }
    //·���ϵĵ� �� 1 3 5 2 ����
    int *trace=NULL;
    trace=(int *)calloc(n,sizeof(int));
    if(trace==NULL)
    {
        printf("No enough memory!\n");
        exit(1);
    }

    visit(ved,trace,a,n);

//��������
    printf("����Ϊ��");
    for(i=0;i<n;i++)
    {
        printf("%d\t",trace[i]);
    }

    free(ved);
    free(trace);
    free(a);
    return 0;
}
