#include <stdio.h>
#include <stdlib.h>

typedef int (*Op)(struct Fun*);
typedef struct func
{
    int a;
    Op op;
}Fun;
int inc(Fun* f)
{
    f->a++;
    printf("%d\n",f->a );
}
int dec(Fun* f)
{
    f->a--;
    printf("%d\n",f->a );
}
int main()
{
    int s;
    scanf("%d",&s );
    Fun* f =(Fun*)malloc(sizeof(Fun));
    f->a=s;
    if(s%2==0)
    {
        f->op=(Op)(inc);
    }
    else
        f->op=(Op)(dec);
    f->op(f);
    return 0;
}
