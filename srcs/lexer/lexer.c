/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:44 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/05 15:25:56 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/lexer.h"
#include "../../incs/utils.h"
#include <errno.h>
#include <stdlib.h>

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
	t_bool	double_quote;

	res = NULL;
	tmp = *line;
	double_quote = FALSE;
	while (*tmp)
	{
		if (*tmp == '\"')
			double_quote = !double_quote;
		if (*tmp == '$' && double_quote == FALSE)
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
