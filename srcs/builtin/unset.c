/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:25 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 22:26:39 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/utils.h"
#include <stdlib.h>

int				builtin_unset(t_list *token_list, int fd);
static t_bool	unset(char *key);
static t_bool	is_correct(t_list *env, char *key);

int	builtin_unset(t_list *token_list, int fd)
{
	t_token	*token;

	token_list = token_list->next;
	while (token_list)
	{
		token = token_list->content;
		if (key_is_not_valid(token->value))
			print_err(1, "unset", token->value, IDENTIFIER_ERR);
		else
			unset(token->value);
		token_list = token_list->next;
	}
	(void) fd;
	return (g_var->exit_status);
}

static t_bool	unset(char *key)
{
	t_list		*prev;
	t_list		*cur;

	prev = NULL;
	cur = g_var->env_list;
	while (cur)
	{
		if (is_correct(cur, key))
		{
			if (prev == NULL)
				g_var->env_list = cur->next;
			else
				prev->next = cur->next;
			ft_lstdelone(cur, free);
			if (prev == NULL)
				cur = g_var->env_list;
			else
				cur = prev->next;
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (TRUE);
}

static t_bool	is_correct(t_list *env, char *key)
{
	size_t	key_len;

	key_len = ft_strlen(env->content);
	if (ft_strchr(env->content, '=') != NULL)
		key_len = ft_strchr(env->content, '=') - (char *) env->content;
	return (ft_strncmp(env->content, key, key_len) == 0);
}
