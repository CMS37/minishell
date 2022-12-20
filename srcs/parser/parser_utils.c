#include "../../incs/minishell.h"
#include <stdlib.h>
/*
int	near_token(const char *s1)
{
	unsigned char	*us1;
	unsigned char	**us2;


	us2 = (unsigned char **)malloc(sizeof(unsigned char *) * 4);
	us2[0] = (unsigned char *)"|";
	us2[1] = (unsigned char *)"&";
	us2[2] = (unsigned char *)";";
	us2[3] = (unsigned char *)"\0";
	us1 = (unsigned char *) s1;
	while ((*us2) != "\-")
	{
		if (us1 == (*us2))
			return (1);
		(*us2)++;
	}
	return (0);
}
int	near_red(const char *s1)
{
	unsigned char	*us1;
	unsigned char	*us2;

	if (!s1)
		return (0);
	us1 = (unsigned char *) s1;
	if (us1 == "<" || us1 == "<<" || us1 == ">" || us1 == ">>")
		return (1);
	return (0);
}*/

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*us1;
	unsigned char	*us2;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (0 - (int) *s2);
	if (!s2)
		return (*s1);
	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	if (*us1 - *us2)
		return (*us1 - *us2);
	return (0);
}
