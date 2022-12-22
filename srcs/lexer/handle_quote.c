#include "../../incs/lexer.h"

t_bool	handle_quote(t_token *token, const char **line);
t_bool	num_of_single_quote_is_odd(const char *line);
t_bool	num_of_double_quote_is_odd(const char *line);
t_bool	handle_single_quote(t_token *token, const char **line);
t_bool	handle_double_quote(t_token *token, const char **line);

t_bool	handle_quote(t_token *token, const char **line)
{
	if (**line == '\'')
		return (handle_single_quote(token, line));
	return (handle_double_quote(token, line));
}

t_bool	num_of_single_quote_is_odd(const char *line)
{
	int		num_of_quote;

	num_of_quote = 0;
	while (*line)
	{
		if (*line == '\'')
			num_of_quote++;
		line++;
	}
	return (num_of_quote % 2 == 1);
}

t_bool	num_of_double_quote_is_odd(const char *line)
{
	int		num_of_quote;

	num_of_quote = 0;
	while (*line)
	{
		if (*line == '\"')
			num_of_quote++;
		line++;
	}
	return (num_of_quote % 2 == 1);
}

t_bool	handle_single_quote(t_token *token, const char **line)
{
	(*line)++;
	while (**line && **line != '\'')
	{
		if (**line == '\"')
			handle_double_quote(token, line);
		else
			token->value = ft_strjoin(token->value, ft_substr(*line, 0, 1));
		(*line)++;
	}
	return (FALSE);
}

t_bool	handle_double_quote(t_token *token, const char **line)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '\'')
			handle_single_quote(token, line);
		else
			token->value = ft_strjoin(token->value, ft_substr(*line, 0, 1));
		(*line)++;
	}
	return (FALSE);
}
