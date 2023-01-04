/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:24 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 22:35:02 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <stdlib.h>

char			*home_dir(void);
char			*get_absolute_path(char *path);
char			*calc_relative_path(char *path);
static t_bool	build_list(t_list **lst, char *path);
static t_bool	ft_dellast(t_list **lst);

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

char	*get_absolute_path(char *path)
{
	char	*ret;

	if (*path == '\0')
		ret = ft_getcwd();
	else if (ft_strcmp(path, "-") == 0)
		ret = get_oldpwd();
	else if (ft_strcmp(path, "~") == 0 || ft_strncmp(path, "~/", 2) == 0)
	{
		ret = home_dir();
		ft_strcat(&ret, path + 1);
	}
	else if (*path != '/')
	{
		ret = ft_getcwd();
		ft_strcat(&ret, "/");
		ft_strcat(&ret, path);
	}
	else
		ret = ft_strdup(path);
	return (ret);
}

char	*calc_relative_path(char *path)
{
	char	*ret;
	t_list	*lst;
	t_list	*tmp;

	ret = NULL;
	lst = NULL;
	build_list(&lst, path);
	tmp = lst;
	while (tmp->next)
	{
		ft_strcat(&ret, tmp->content);
		tmp = tmp->next;
	}
	if (((char *) tmp->content)[ft_strlen(tmp->content) - 1] == '/')
		ft_strncat(&ret, tmp->content, ft_strlen(tmp->content) - 1);
	else
		ft_strcat(&ret, tmp->content);
	ft_lstclear(&lst, free);
	return (ret);
}

static t_bool	build_list(t_list **lst, char *path)
{
	char	*token;

	token = NULL;
	while (*path)
	{
		ft_strncat(&token, path, 1);
		if (*path == '/' || *(path + 1) == '\0')
		{
			if (ft_strcmp(token, ".") == 0 || ft_strcmp(token, "./") == 0)
				free(token);
			else if (!ft_strcmp(token, "..") || !ft_strcmp(token, "../"))
			{
				free(token);
				ft_dellast(lst);
			}
			else
				ft_lstadd_back(lst, ft_lstnew(token));
			token = NULL;
		}
		path++;
	}
	return (TRUE);
}

static t_bool	ft_dellast(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp->next == NULL)
	{
		free(tmp->content);
		free(tmp);
		*lst = NULL;
		return (TRUE);
	}
	while (tmp->next->next)
		tmp = tmp->next;
	free(tmp->next->content);
	free(tmp->next);
	tmp->next = NULL;
	return (TRUE);
}
