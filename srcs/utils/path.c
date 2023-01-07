/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:24 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/08 00:12:43 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <unistd.h>

char	*home_dir(void);
char	*ft_getcwd(void);
char	*get_oldpwd(void);

char	*home_dir(void)
{
	t_list	*tmp;

	tmp = g_var->env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "HOME=", 5) == 0)
			return (ft_strdup(tmp->content + 5));
		tmp = tmp->next;
	}
	export("HOME=/Users/younhwan");
	return (ft_strdup("/Users/younhwan"));
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
