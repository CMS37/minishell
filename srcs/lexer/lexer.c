#include "../../libs/libft/incs/libft.h"
#include "../../incs/lexer.h"
#include "../../incs/subsystem.h"
#include "../../incs/utils.h"
#include <errno.h>

t_bool			lexer(const char *line);
static t_bool	num_of_quote_is_odd(const char *line);

t_bool	lexer(const char *line)
{
	if (num_of_quote_is_odd(line))
		return (print_err(EINVAL, (char *) line, NULL, QUOTE_ERR) == 0);
	ft_lstclear(&g_var->token_list, del_token);
	tokenize(line);
	return (TRUE);
}

t_bool	num_of_quote_is_odd(const char *line)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*line)
	{
		if (*line == '\'')
			single_quote++;
		else if (*line == '\"')
			double_quote++;
		line++;
	}
	return ((single_quote % 2) || (double_quote % 2));
}
