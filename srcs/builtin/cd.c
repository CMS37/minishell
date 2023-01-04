/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:07 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/05 00:26:54 by younhwan         ###   ########.fr       */
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
static int		chdir_to_home(char *cwd);
static t_bool	convert_to_absolute_path(char **path);
static t_bool	set_path_env(char *oldpwd, char *pwd);

int	builtin_cd(t_list *token_list, int fd)
{
	char *const		cwd = ft_getcwd();
	t_token			*arg;
	char			*to_go;

	(void) fd;
	if (cwd == NULL)
		return (print_err(errno, "cd", NULL, strerror(errno)));
	if (ft_lstsize(token_list) == 1)
		return (chdir_to_home(cwd));
	arg = token_list->next->content;
	if (convert_to_absolute_path(&arg->value) == FALSE)
	{
		free(cwd);
		return (print_err(1, "cd", NULL, "OLDPWD not set"));
	}
	to_go = arg->value;
	if (to_go == NULL || chdir(to_go) != 0)
		print_err(errno, "cd", arg->value, strerror(errno));
	set_path_env(cwd, to_go);
	return (g_var->exit_status);
}

static int	chdir_to_home(char *cwd)
{
	char *const	home = home_dir();
	int			ret;

	ret = 0;
	if (home == NULL || chdir(home) != 0)
		ret = errno;
	set_path_env(cwd, home);
	if (home != NULL)
		free(home);
	if (ret != 0)
		print_err(ret, "cd", NULL, strerror(ret));
	return (set_exit_status(ret));
}

static t_bool	convert_to_absolute_path(char **path)
{
	char *const		before_calculated = get_absolute_path(*path);
	const t_bool	chdir_to_oldpwd = ((**path) == '-');
	char			*calculated;

	if (ft_strcmp(*path, "-") == 0 && before_calculated == NULL)
		return (FALSE);
	calculated = calc_relative_path(before_calculated);
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
	if (chdir_to_oldpwd)
		ft_putendl_fd(*path, 1);
	return (TRUE);
}

static t_bool	set_path_env(char *oldpwd, char *pwd)
{
	char *const	old_path = ft_strjoin("OLDPWD=", oldpwd);
	char *const	cur_path = ft_strjoin("PWD=", pwd);

	export(old_path);
	export(cur_path);
	free(oldpwd);
	free(old_path);
	free(cur_path);
	return (TRUE);
}
