#include "main.h"
/**
 * main - print alphabet
 * Return: 0
*/
void print_alphabet(void)
{
	char ch;
	int i;

	i = 0;

	while (i < 10)
	{
	ch = 'a';
	while (ch <= 'z')
	{
	_putchar(ch);
	ch++;
	}
	_putchar('\n')
	i++;
	}
}
