/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:29 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/15 14:26:23 by younhwan         ###   ########.fr       */
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
t_bool	execute_builtin(t_list *token_list, t_bool child_process);

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

t_bool	execute_builtin(t_list *token_list, t_bool child_process)
{
	t_token *const	token = (t_token *) token_list->content;
	int				fd;
	size_t			i;

	if (set_fd_in_redir(&token_list) == FALSE)
		return (TRUE);
	fd = 1;
	if (child_process == FALSE && ft_strcmp(token->value, "exit") == 0)
		fd = 2;
	i = 0;
	set_exit_status(0);
	set_underscore_env();
	while (g_builtin_list[i] != NULL)
	{
		if (ft_strcmp(token->value, g_builtin_list[i]) == 0)
			return (g_builtin_func[i](token_list, fd));
		i++;
	}
	return (TRUE);
}
