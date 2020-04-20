#ifndef _CHAR_FUNCTIONS_H
#define _CHAR_FUNCTIONS_H

int cmp_char(void *c1, void *c2)
{

    int a = (int)c1;
    int b = (int)c2;

    if (a == b)
    {
        return 0;
    }
    else if (a < b)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void print_node(RBNODE n)
{
    printf("%c ", (char)n->key);
}

#define CMP_CHAR &cmp_char
#define PRINT_CHAR &print_node

#endif // _CHAR_FUNCTIONS