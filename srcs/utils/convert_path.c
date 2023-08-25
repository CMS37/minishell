/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 00:51:45 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/09 15:00:40 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"
#include <stdlib.h>
#include <unistd.h>

t_bool			convert_path(char **path);
char			*get_absolute_path(char *path);
char			*calc_relative_path(char *path);
static t_bool	build_list(t_list **lst, char *path);
static t_bool	ft_dellast(t_list **lst);

t_bool	convert_path(char **path)
{
	char *const		before_calculated = get_absolute_path(*path);
	char			*calculated;

	if (before_calculated == NULL)
		return (FALSE);
	calculated = calc_relative_path(before_calculated);
	if (calculated == NULL)
		return (FALSE);
	free(*path);
	if (access(calculated, F_OK) == 0)
	{
		*path = calculated;
		free(before_calculated);
	}
	else
	{
		*path = before_calculated;
		free(calculated);
	}
	return (TRUE);
}

char	*get_absolute_path(char *path)
{
	char	*ret;

	if (*path == '\0')
		ret = ft_getcwd();
	else if (ft_strcmp(path, "-") == 0)
		ret = get_oldpwd();
	else if (ft_strcmp(path, "~") == 0 || ft_strncmp(path, "~/", 2) == 0)
		ret = home_dir();
	else if (*path != '/')
		ret = ft_getcwd();
	else
		ret = ft_strdup(path);
	if (ret == NULL)
		return (NULL);
	if (ft_strcmp(path, "~") == 0 || ft_strncmp(path, "~/", 2) == 0)
		ft_strcat(&ret, path + 1);
	else if (*path != '\0' && *path != '-' && *path != '/')
	{
		ft_strcat(&ret, "/");
		ft_strcat(&ret, path);
	}
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
