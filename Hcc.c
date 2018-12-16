#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "引数の個数が正しくありません。\nUsage: Hcc <code>\n");
        return 1;
    }

    char *p = argv[1];

    printf(".globl _main\n");
    printf("_main:\n");
    printf("  movl  $%ld, %%eax\n", strtol(p, &p, 10));

    while (*p)
    {
        if (*p == '+')
        {
            p++;
            printf("  addl  $%ld, %%eax\n", strtol(p, &p, 10));
            continue;
        }
        if (*p == '-')
        {
            p++;
            printf("  subl  $%ld, %%eax\n", strtol(p, &p, 10));
            continue;
        }
        fprintf(stderr, "予期されていない文字です。: %c\n", *p);
        return 1;
    }

    printf("  ret\n");
    return 0;
}