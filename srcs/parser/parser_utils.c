#include "../../incs/minishell.h"
#include <stdlib.h>

/*
	T_PIPE = 2,
	T_REDIRECT = 3,
	T_SINGLE_QUOTE = 4,
	T_DOUBLE_QUOTE = 5,
*/

t_bool	is_unexpected_token(const char *token);

t_bool	is_unexpected_token(const char *token)
{
	if (!ft_strcmp(token, "|"))
		return (TRUE);
	if (!ft_strcmp(token, ">") || !ft_strcmp(token, "<"))
		return (TRUE);
	if (!ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
		return (TRUE);
	if (!ft_strcmp(token, "'") || !ft_strcmp(token, "\""))
		return (TRUE);
	return (FALSE);
}

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
}
*/
