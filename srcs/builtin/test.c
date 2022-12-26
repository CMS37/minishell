#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	int			tmp;
	long long	i;

//	strerror(errno);
//	printf("%s\n", strerror(2323));	
	tmp = 0;
	i = -2323232323;
	i = (256 - ((i * -1) % 256));
	tmp = i;
	printf ("num : %d\n", tmp);
	return (1);
}