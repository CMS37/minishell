/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:11 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/05 17:51:16 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <stdlib.h>

int		builtin_env(t_list *token_list, int fd);
t_list	*get_env(const char *key);
t_bool	init_env_list(int argc, char **argv, char **envp);

int	builtin_env(t_list *token_list, int fd)
{
	t_list	*cur_list;
	char	*cur_env;

	cur_list = g_var->env_list;
	while (cur_list != NULL)
	{
		cur_env = (char *) cur_list->content;
		if (ft_strchr(cur_env, '=') != NULL)
			ft_putendl_fd(cur_env, fd);
		cur_list = cur_list->next;
	}
	(void) token_list;
	return (g_var->exit_status);
}

t_list	*get_env(const char *key)
{
	t_list	*ret;
	size_t	key_len;

	ret = g_var->env_list;
	key_len = ft_strlen(key);
	if (ft_strchr(key, '=') != NULL)
		key_len = ft_strchr(key, '=') - key + 1;
	while (ret)
	{
		if (ft_strncmp(ret->content, key, key_len) == 0)
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

t_bool	init_env_list(int argc, char **argv, char **envp)
{
	char *const	last_exec = ft_strjoin("_=", argv[argc - 1]);
	char *const	shlvl = ft_strdup("SHLVL=");
	char		*lvl;

	lvl = NULL;
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "SHLVL", 5) == 0)
			lvl = ft_itoa(ft_atoi(*envp + 6) + 1);
		if (ft_strncmp(*envp, "OLDPWD", 6) == 0)
			envp++;
		else
			ft_lstadd_back(&g_var->env_list, ft_lstnew(ft_strdup(*envp++)));
	}
	if (lvl == NULL || ft_atoi(lvl) <= 0)
		ft_strcat((char **) &shlvl, "1");
	else
		ft_strcat((char **) &shlvl, lvl);
	free(lvl);
	export(shlvl);
	export(last_exec);
	free(shlvl);
	free(last_exec);
	return (TRUE);
}
