/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:31 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 14:58:30 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute.h"
#include "../../incs/builtin.h"
#include "../../incs/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

void			execute_extern(t_list *token_list);
static char		**list_to_arr(t_list *token_list);
static char		*find_path(const char *cmd);
static t_bool	free_paths(char **paths);

void	execute_extern(t_list *token_list)
{
	char **const	cmd = list_to_arr(token_list);
	char			*path;
	DIR				*dir;

	if (convert_to_absolute_path(&cmd[0]) == FALSE)
		exit(print_err(errno, cmd[0], NULL, strerror(errno)));
	if (*cmd[0] == '/')
		path = ft_strdup(cmd[0]);
	else
		path = find_path(cmd[0]);
	if (path == NULL)
		exit(print_err(127, cmd[0], NULL, CMD_ERR));
	if (access(path, F_OK) != 0)
		exit(print_err(127, cmd[0], NULL, "No such file or directory"));
	dir = opendir(path);
	if (dir != NULL && closedir(dir) == 0)
		exit(print_err(126, path, NULL, "is a directory"));
	if (access(path, X_OK) != 0)
		exit(print_err(126, cmd[0], NULL, "permission denied"));
	set_exit_status(0);
	if (execve(path, cmd, ft_getenv()) == -1)
		exit(print_err(errno, cmd[0], NULL, strerror(errno)));
	ft_putendl_fd("This is easter egg!!", 2);
}

static char	**list_to_arr(t_list *token_list)
{
	const size_t	sz = ft_lstsize(token_list);
	char **const	ret = ft_calloc(sizeof(char *), sz + 1, "");
	size_t			i;

	i = 0;
	while (i < sz)
	{
		ret[i] = ft_strdup(((t_token *) token_list->content)->value);
		token_list = token_list->next;
		i++;
	}
	return (ret);
}

static char	*find_path(const char *cmd)
{
	char	*ret;
	char	**paths;
	t_list	*tmp;
	size_t	i;

	tmp = g_var->env_list;
	while (ft_strnstr(tmp->content, "PATH=", 5) == NULL)
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	paths = ft_split(tmp->content + 5, ':');
	i = 0;
	while (paths[i])
	{
		ret = ft_strjoin(paths[i], "/");
		ft_strcat(&ret, cmd);
		if (access(ret, F_OK) == 0 && free_paths(paths))
			return (ret);
		free(ret);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

static t_bool	free_paths(char **paths)
{
	char	**tmp;

	if (paths == NULL)
		return (TRUE);
	tmp = paths;
	while (*tmp)
		free(*tmp++);
	free(paths);
	return (TRUE);
}
