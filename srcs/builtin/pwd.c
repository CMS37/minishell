/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:23 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 22:54:54 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int		builtin_pwd(t_list *token_list, int fd);
char	*ft_getcwd(void);
char	*get_oldpwd(void);

int	builtin_pwd(t_list *token_list, int fd)
{
	char	*pwd;

	pwd = ft_getcwd();
	if (pwd == NULL)
		return (print_err(errno, "pwd", NULL, strerror(errno)));
	ft_putendl_fd(pwd, fd);
	free(pwd);
	(void) token_list;
	return (g_var->exit_status);
}

char	*ft_getcwd(void)
{
	char	*ret;
	t_list	*env_tmp;

	ret = getcwd(NULL, 0);
	if (ret != NULL)
		return (ret);
	env_tmp = g_var->env_list;
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->content, "PWD=", 4) == 0)
		{
			ret = ft_strdup(env_tmp->content + 4);
			break ;
		}
		env_tmp = env_tmp->next;
	}
	return (ret);
}

char	*get_oldpwd(void)
{
	t_list	*env_tmp;

	env_tmp = g_var->env_list;
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->content, "OLDPWD=", 7) == 0)
			return (ft_strdup(env_tmp->content + 7));
		env_tmp = env_tmp->next;
	}
	return (NULL);
}
