#include <stdio.h>
#include <stdlib.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start,size_t len)
{
    size_t i;
    for(i=0;i<len;i++)
    {
        printf(" %.2x",start[i]);
    }
    putchar('\n');
}


struct SAM_struct
{
    char  c;
    int   i;
    float f;
};

union SAM_union
{
    char  c;
    int   i;
    float f;
};

enum {no,yes,none} sam_enu;

int *sam_p=NULL;

int sam_a[3]={1,2,3};

int main()
{
    struct SAM_struct sam_str;
    sam_str.c='s';
    sam_str.i=1;
    sam_str.f=1.1;

    union SAM_union sam_uni;
    sam_uni.c='u';
    sam_uni.i=2;
    sam_uni.f=2.2;

    int sample=1;
    sam_p=&sample;

    printf("变量名 :\t内容  \t  \t\t\t地址\t内存各字节\n");

    printf("sam_p  :\t%d(指向)\t%x(地址)\t  \t%x\t",*sam_p,sam_p,&sam_p);
    show_bytes((byte_pointer)&sam_p,sizeof(int *));

    printf("sam_a  :\t%d\t%d\t%d\t\t%x\t",sam_a[0],sam_a[1],sam_a[2],sam_a);
    show_bytes((byte_pointer)sam_a,3*sizeof(int));

    printf("sam_str:\t%c\t%d\t%f\t%x\t",sam_str.c,sam_str.i,sam_str.f,&sam_str);
    show_bytes((byte_pointer)&sam_str,sizeof(struct SAM_struct));

    printf("sam_uni:\t%c\t%d\t%f\t%x\t",sam_uni.c,sam_uni.i,sam_uni.f,&sam_uni);
    show_bytes((byte_pointer)&sam_uni,sizeof(union SAM_union));

    printf("sam_enu:\t%d\t%d\t%d\t\t%x\t",no,yes,none,&sam_enu);
    show_bytes((byte_pointer)&sam_enu,sizeof(int));
    //putchar('\n');
    printf("main   :\t\t\t\t\t%x\n",&main);
    printf("printf :\t\t\t\t\t%x\n",&printf);

    return 0;
}
