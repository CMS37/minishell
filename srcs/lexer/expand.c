/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:39 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/13 01:22:27 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/lexer.h"
#include "../../incs/builtin.h"
#include <stdlib.h>

char			*expand(char **line);
t_bool			is_expand(int c);
static char		*get_key(char **line);
static size_t	get_key_size(char *line);
static char		*get_value(char *key);

char	*expand(char **line)
{
	char *const	key = get_key(line);
	char		*ret;

	if (key == NULL && (*(*line + 1) == '\0' || *(*line + 1) == '$'))
		ret = ft_strdup("$");
	else if (key == NULL || key_is_not_valid(key))
		ret = NULL;
	else if (key[0] == '?')
		ret = ft_itoa(g_var->exit_status);
	else
		ret = ft_strdup(get_value(key));
	if (key != NULL)
		free(key);
	return (ret);
}

t_bool	is_expand(int c)
{
	return (c == '$');
}

static char	*get_key(char **line)
{
	const int	key_size = get_key_size(*line + 1);
	char		*ret;

	if (key_size == 0)
		return (NULL);
	ret = ft_calloc(sizeof(char), key_size + 1, "");
	ft_strlcpy(ret, *line + 1, key_size + 1);
	*line += key_size;
	return (ret);
}

static size_t	get_key_size(char *line)
{
	size_t	ret;

	if (*line == '?')
		return (1);
	ret = 0;
	while (line[ret] && is_not_word(line[ret]) == FALSE)
		ret++;
	return (ret);
}

static char	*get_value(char *key)
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
