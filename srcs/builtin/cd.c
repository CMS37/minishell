/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:07 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 23:18:28 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/lexer.h"
#include "../../incs/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int				builtin_cd(t_list *token_list, int fd);
static int		chdir_to_home(char *oldpwd);
static t_bool	convert_to_absolute_path(char **path);
static t_bool	set_path_env(char *oldpwd, char *pwd);

int	builtin_cd(t_list *token_list, int fd)
{
	char *const		oldpwd = ft_getcwd();
	t_token			*arg;
	char			*path;

	(void) fd;
	if (oldpwd == NULL)
		return (print_err(errno, "cd", NULL, strerror(errno)));
	if (ft_lstsize(token_list) == 1)
		return (chdir_to_home(oldpwd));
	arg = token_list->next->content;
	if (convert_to_absolute_path(&arg->value) == FALSE)
	{
		free(oldpwd);
		return (print_err(1, "cd", NULL, "OLDPWD not set"));
	}
	path = arg->value;
	if (path == NULL || chdir(path) != 0)
		print_err(errno, "cd", arg->value, strerror(errno));
	set_path_env(oldpwd, path);
	return (g_var->exit_status);
}

static int	chdir_to_home(char *oldpwd)
{
	char *const	home = home_dir();
	int			ret;

	ret = 0;
	if (home == NULL || chdir(home) != 0)
		ret = errno;
	set_path_env(oldpwd, home);
	if (home != NULL)
		free(home);
	if (ret != 0)
		print_err(ret, "cd", NULL, strerror(ret));
	return (set_exit_status(ret));
}

static t_bool	convert_to_absolute_path(char **path)
{
	char *const	before_calculated = get_absolute_path(*path);
	char		*calculated;

	if (ft_strcmp(*path, "-") == 0 && before_calculated == NULL)
		return (FALSE);
	free(*path);
	calculated = calc_relative_path(before_calculated);
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

static t_bool	set_path_env(char *oldpwd, char *pwd)
{
	t_list		*env;
	char *const	old_path = ft_strjoin("OLDPWD=", oldpwd);
	char *const	cur_path = ft_strjoin("PWD=", pwd);

	env = get_env("OLDPWD");
	if (env == NULL)
		ft_lstadd_back(&g_var->env_list, ft_lstnew(old_path));
	else
		replace_value(env, old_path);
	env = get_env("PWD");
	if (env == NULL)
		ft_lstadd_back(&g_var->env_list, ft_lstnew(cur_path));
	else
		replace_value(env, cur_path);
	free(oldpwd);
	return (TRUE);
}
