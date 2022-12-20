#include "../../incs/lexer.h"

t_bool	is_ifs(int c);
t_bool	is_meta(int c);

t_bool	is_ifs(int c)
{
	return ((9 <= c && c <= 13) || c == 32);
}

t_bool	is_meta(int c)
{
	char const	*meta = "><$|\'\"";
	size_t		i;

	i = 0;
	while (meta[i])
	{
		if (c == meta[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}
