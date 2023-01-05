/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:20 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/05 17:51:03 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/utils.h"
#include <stdlib.h>

int				builtin_export(t_list *token_list, int fd);
t_bool			export(char *value);
t_bool			key_is_not_valid(const char *key);
static t_bool	replace_value(t_list *env, const char *envp);
static int		print_export(int fd);

int	builtin_export(t_list *token_list, int fd)
{
	char	*value;

	if (ft_lstsize(token_list) == 1)
		return (print_export(fd));
	token_list = token_list->next;
	while (token_list)
	{
		value = ((t_token *) token_list->content)->value;
		if (key_is_not_valid(value))
			print_err(1, "export", value, IDENTIFIER_ERR);
		else
			export(value);
		token_list = token_list->next;
	}
	return (g_var->exit_status);
}

t_bool	export(char *value)
{
	t_list *const	last_executed = ft_lstlast(g_var->env_list);
	t_list *const	env = get_env(value);

	if (env == NULL)
	{
		ft_lstadd_back(&g_var->env_list, ft_lstnew(ft_strdup(value)));
		ft_swap(&last_executed->content, &last_executed->next->content);
	}
	else
		replace_value(env, value);
	return (TRUE);
}

t_bool	key_is_not_valid(const char *key)
{
	if (*key == 0)
		return (TRUE);
	if (*key == '?')
		return (FALSE);
	if (ft_isalpha(*key) == 0 && *key != '_')
		return (TRUE);
	while (*key)
	{
		if (*key == '=')
			break ;
		if (ft_isalnum(*key) == 0 && *key != '_')
			return (TRUE);
		key++;
	}
	return (FALSE);
}

static t_bool	replace_value(t_list *env, const char *envp)
{
	if (ft_strchr(envp, '=') == NULL)
		return (TRUE);
	if (env->content != NULL)
		free(env->content);
	env->content = ft_strdup(envp);
	return (TRUE);
}

static int	print_export(int fd)
{
	t_list	*env;
	char	*c;

	env = g_var->env_list;
	while (env->next)
	{
		ft_putstr_fd("declare -x ", fd);
		c = env->content;
		while (*c && *c != '=')
			ft_putchar_fd(*c++, fd);
		if (*c == '=')
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(c + 1, fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
		env = env->next;
	}
	return (g_var->exit_status);
}
