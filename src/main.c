/**
 * Entry point into application
 * 
 * @file main.c
 * @date 04/18/2020
 */

#include <stdio.h>
#include <rbtree.h>

int cmp_char(void *c1, void *c2) {
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

int main(void)
{

}
