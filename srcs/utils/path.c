/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:24 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 18:31:26 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <stdlib.h>

char			*home_dir(void);
t_bool			convert_to_absolute_path(char **path);
static t_bool	calc_relative_path(char **path);
static t_bool	build_list(t_list **lst, char **path);
static t_bool	ft_dellast(t_list **lst);

char	*home_dir(void)
{
	t_list	*tmp;

	tmp = g_var->env_list;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, "HOME=", 5) != 0)
			return (ft_strdup(tmp->content + 5));
		tmp = tmp->next;
	}
	return (NULL);
}

t_bool	convert_to_absolute_path(char **path)
{
	char	*ret;
	char	*if_not_exists;

	if (**path == '\0')
		ret = ft_getcwd();
	else if (**path != '/')
	{
		ret = ft_getcwd();
		ft_strcat(&ret, "/");
		ft_strcat(&ret, *path);
	}
	else
		ret = ft_strdup(*path);
	if_not_exists = ft_strdup(ret);
	calc_relative_path(&ret);
	free(*path);
	if (access(ret, F_OK) == -1)
	{
		free(ret);
		ret = if_not_exists;
	}
	else
		free(if_not_exists);
	*path = ret;
	return (TRUE);
}

static t_bool	calc_relative_path(char **path)
{
	t_list	*ret;
	t_list	*tmp;

	ret = NULL;
	build_list(&ret, path);
	free(*path);
	*path = NULL;
	tmp = ret;
	while (tmp->next)
	{
		ft_strcat(&(*path), tmp->content);
		tmp = tmp->next;
	}
	if (((char *) tmp->content)[ft_strlen(tmp->content) - 1] == '/')
		ft_strncat(&(*path), tmp->content, ft_strlen(tmp->content) - 1);
	else
		ft_strcat(&(*path), tmp->content);
	ft_lstclear(&ret, free);
	return (TRUE);
}

static t_bool	build_list(t_list **lst, char **path)
{
	char	*tmp;
	char	*token;

	tmp = *path;
	token = NULL;
	while (*tmp)
	{
		ft_strncat(&token, tmp, 1);
		if (*tmp == '/' || *(tmp + 1) == '\0')
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
		tmp++;
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
