/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:46 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 14:58:30 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/lexer.h"

t_bool	handle_meta(const char **line);
t_bool	is_meta(int c);
t_token	*init_meta_token(const char **line);

t_bool	handle_meta(const char **line)
{
	t_token *const	meta = init_meta_token(line);

	ft_lstadd_back(&g_var->token_list, ft_lstnew(meta));
	return (TRUE);
}

t_bool	is_meta(int c)
{
	const char	meta[4] = {'|', '>', '<', '\0'};
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

t_token	*init_meta_token(const char **line)
{
	t_token *const	ret = init_token();

	if (**line == '|')
		ret->type = T_PIPE;
	else if (**line == '>' || **line == '<')
		ret->type = T_REDIRECT;
	ft_strncat(&ret->value, *line, 1);
	if (ret->type == T_REDIRECT && **line == *(*line + 1))
		ft_strncat(&ret->value, ++(*line), 1);
	return (ret);
}
