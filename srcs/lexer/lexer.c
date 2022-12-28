#include "../../libs/libft/incs/libft.h"
#include "../../incs/lexer.h"
#include "../../incs/subsystem.h"
#include <errno.h>

t_bool	lexer(const char *line);

t_bool	lexer(const char *line)
{
	if (num_of_single_quote_is_odd(line) || num_of_double_quote_is_odd(line))
		return (print_err(EINVAL, (char *) line, NULL, QUOTE_ERR) == 0);
	ft_lstclear(&g_var->token_list, del_token);
	tokenize(line);
	return (TRUE);
}
