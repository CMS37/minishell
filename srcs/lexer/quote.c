#include "../../incs/lexer.h"

t_bool			handle_quote(t_token *token, const char **line);
t_bool			is_quote(int c);
static t_bool	handle_single_quote(t_token *token, const char **line);
static t_bool	handle_double_quote(t_token *token, const char **line);

t_bool	handle_quote(t_token *token, const char **line)
{
	if (**line == '\'')
		return (handle_single_quote(token, line));
	return (handle_double_quote(token, line));
}

t_bool	is_quote(int c)
{
	return (c == '\'' || c == '\"');
}

static t_bool	handle_single_quote(t_token *token, const char **line)
{
	(*line)++;
	while (**line && **line != '\'')
		ft_strncat(&token->value, (*line)++, 1);
	return (FALSE);
}

static t_bool	handle_double_quote(t_token *token, const char **line)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '$')
			ft_strcat(&token->value, expand(line));
		else
			ft_strncat(&token->value, *line, 1);
		(*line)++;
	}
	return (FALSE);
}
