/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:39 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 14:58:30 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/lexer.h"
#include <stdlib.h>

char			*expand(const char **line);
t_bool			is_expand(int c);
static char		*get_key(const char **line);
static size_t	get_key_size(const char *line);
static char		*get_value(const char *key);

char	*expand(const char **line)
{
	char *const	key = get_key(line);
	char		*ret;

	if (key[0] == '?')
		ret = ft_itoa(g_var->exit_status);
	else
		ret = get_value(key);
	free(key);
	return (ret);
}

t_bool	is_expand(int c)
{
	return (c == '$');
}

static char	*get_key(const char **line)
{
	const int	key_size = get_key_size(*line + 1);
	char *const	ret = ft_calloc(sizeof(char), key_size + 1, "");

	ft_strlcpy(ret, *line + 1, key_size + 1);
	*line += key_size;
	return (ret);
}

static size_t	get_key_size(const char *line)
{
	size_t	ret;

	if (*line == '?')
		return (1);
	ret = 0;
	while (line[ret] && is_not_word(line[ret]) == FALSE)
		ret++;
	return (ret);
}

static char	*get_value(const char *key)
{
	t_list	*tmp;
	size_t	key_len;

	tmp = g_var->env_list;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(key, tmp->content, key_len) == 0 && \
			((char *)tmp->content)[key_len] == '=')
			return (tmp->content + key_len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}
