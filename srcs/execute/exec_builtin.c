/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-cho <min-cho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:29 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 18:36:18 by min-cho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute.h"
#include "../../incs/builtin.h"

const static char	*g_builtin_list[] = {
	"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL
};

int static (*const	g_builtin_func[])(t_list *token_list, int fd) = {
	builtin_cd, builtin_echo, builtin_env, builtin_exit,
	builtin_export, builtin_pwd, builtin_unset, NULL
};

t_bool	is_builtin(t_list *token_list);
t_bool	execute_builtin(t_list *token_list);

t_bool	is_builtin(t_list *token_list)
{
	char	**tmp;
	t_token	*token;

	tmp = (char **) g_builtin_list;
	token = (t_token *) token_list->content;
	while (*tmp)
	{
		if (ft_strcmp(token->value, *tmp) == 0)
			return (TRUE);
		tmp++;
	}
	return (FALSE);
}

t_bool	execute_builtin(t_list *token_list)
{
	t_token	*token;
	size_t	i;

	if (set_fd_in_redir(token_list) == FALSE)
		return (TRUE);
	token = (t_token *) token_list->content;
	i = 0;
	set_exit_status(0);
	set_underscore_env();
	while (g_builtin_list[i] != NULL)
	{
		if (ft_strcmp(token->value, g_builtin_list[i]) == 0)
			return (g_builtin_func[i](token_list, 1));
		i++;
	}
	return (TRUE);
}
