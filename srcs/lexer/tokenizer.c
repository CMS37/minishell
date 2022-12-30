#include "../../libs/libft/incs/libft.h"
#include "../../incs/lexer.h"
#include <stdlib.h>

t_bool			tokenize(const char *line);
t_bool			is_not_word(int c);
static t_bool	handle_tokens(t_token **token, const char **line, t_bool *flag);

t_bool	tokenize(const char *line)
{
	t_bool	quote_exists;
	t_token	*cur;

	quote_exists = FALSE;
	cur = init_token();
	while (*line)
	{
		if (is_not_word(*line))
			handle_tokens(&cur, &line, &quote_exists);
		else
			ft_strncat(&cur->value, line, 1);
		line++;
	}
	if (cur->value[0] != '\0' || quote_exists == TRUE)
		ft_lstadd_back(&g_var->token_list, ft_lstnew(cur));
	else
		del_token(cur);
	return (TRUE);
}

t_bool	is_not_word(int c)
{
	return (
		is_ifs(c) || \
		is_meta(c) || \
		is_quote(c) || \
		is_expand(c)
	);
}

static t_bool	handle_tokens(t_token **token, const char **line, t_bool *flag)
{
	if ((is_ifs(**line) || is_meta(**line)) &&
		((*token)->value[0] != '\0' || *flag == TRUE))
	{
		ft_lstadd_back(&g_var->token_list, ft_lstnew(*token));
		*token = init_token();
		*flag = FALSE;
	}
	if (is_meta(**line))
		handle_meta(line);
	else if (is_quote(**line))
	{
		handle_quote(*token, line);
		*flag = TRUE;
	}
	else if (is_expand(**line))
		handle_expand(*token, line);
	return (TRUE);
}
