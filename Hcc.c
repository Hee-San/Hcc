#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum
{
    TK_NUM = 256,
    TK_EOF,
};

typedef struct
{
    int ty;
    int val;
    char *input;
} Token;

Token tokens[100];

void tokenize(char *p)
{
    int i = 0;
    while (*p)
    {
        if (isspace(*p))
        {
            p++;
            continue;
        }

        if (*p == '+' || *p == '-')
        {
            tokens[i].ty = *p;
            tokens[i].input = p;
            i++;
            p++;
            continue;
        }

        if (isdigit(*p))
        {
            tokens[i].ty = TK_NUM;
            tokens[i].input = p;
            tokens[i].val = strtol(p, &p, 10);
            i++;
            continue;
        }

        fprintf(stderr, "字句解析できません: %s\n", p);
        exit(1);
    }

    tokens[i].ty = TK_EOF;
    tokens[i].input = p;
}

void error(int i)
{
    fprintf(stderr, "予期せぬトークンです。: %s\n", tokens[i].input);
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "引数の個数が正しくありません。\nUsage: Hcc <code>\n");
        return 1;
    }

    tokenize(argv[1]);

    printf(".globl _main\n");
    printf("_main:\n");

    if (tokens[0].ty != TK_NUM)
        error(0);

    printf("  movl  $%d, %%eax\n", tokens[0].val);

    int i = 1;
    while (tokens[i].ty != TK_EOF)
    {
        if (tokens[i].ty == '+')
        {
            i++;
            if (tokens[i].ty != TK_NUM)
                error(i);
            printf("  addl  $%d, %%eax\n", tokens[i].val);
            i++;
            continue;
        }

        if (tokens[i].ty == '-')
        {
            i++;
            if (tokens[i].ty != TK_NUM)
                error(i);
            printf("  subl  $%d, %%eax\n", tokens[i].val);
            i++;
            continue;
        }
        error(i);
    }

    printf("  ret\n");
    return 0;
}
