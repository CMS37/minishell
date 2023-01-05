/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:44 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/05 17:45:12 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/lexer.h"
#include "../../incs/utils.h"
#include <errno.h>
#include <stdlib.h>

const static size_t	g_single_quote_mask = 2;
const static size_t	g_double_quote_mask = 1;

t_bool			lexer(char **line);
static t_bool	expand_vars(char **line);
static t_bool	expand_var(char **res, char **iter);

t_bool	lexer(char **line)
{
	if (**line == '\0')
		return (FALSE);
	if (expand_vars(line) == FALSE)
		return (print_err(1, *line, NULL, IDENTIFIER_ERR));
	if (tokenize(*line) == FALSE)
		return (print_err(EINVAL, *line, NULL, QUOTE_ERR) == 0);
	return (TRUE);
}

static t_bool	expand_vars(char **line)
{
	char	*res;
	char	*tmp;
	size_t	quote;

	res = NULL;
	tmp = *line;
	quote = 0;
	while (*tmp)
	{
		quote ^= (g_single_quote_mask * (*tmp == '\''));
		quote ^= (g_double_quote_mask * (*tmp == '"'));
		if (*tmp == '$' && quote == 0)
		{
			if (expand_var(&res, &tmp) == FALSE)
				return (FALSE);
		}
		else
			ft_strncat(&res, tmp, 1);
		tmp++;
	}
	free(*line);
	*line = res;
	return (TRUE);
}

static t_bool	expand_var(char **res, char **iter)
{
	char *const	exp = expand(iter);

	if (exp == NULL)
	{
		free(*res);
		return (FALSE);
	}
	ft_strcat(res, exp);
	free(exp);
	return (TRUE);
}
