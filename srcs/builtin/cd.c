/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:07 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/09 23:32:09 by younhwan         ###   ########.fr       */
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
static int		chdir_to_arg(t_list *token_list, char *cwd, int fd);
static t_bool	set_path_env(char *oldpwd, char *pwd);

int	builtin_cd(t_list *token_list, int fd)
{
	char *const	cwd = ft_getcwd();
	int			exit_status;

	if (cwd == NULL)
		return (print_err(errno, "cd", NULL, "PWD not set"));
	if (ft_lstsize(token_list) == 1)
		exit_status = chdir_to_home(cwd);
	else
		exit_status = chdir_to_arg(token_list, cwd, fd);
	free(cwd);
	if (exit_status == 1 << 16)
		exit_status = 1;
	else if (exit_status != 0)
		print_err(errno, "cd", NULL, strerror(errno));
	return (set_exit_status(exit_status));
}

static int	chdir_to_home(char *cwd)
{
	char *const	home = home_dir();
	int			ret;

	ret = 0;
	if (home == NULL)
	{
		ret = 1 << 16;
		print_err(1, "cd", NULL, "Home not set");
	}
	else if (chdir(home) != 0)
		ret = errno;
	set_path_env(cwd, home);
	if (home != NULL)
		free(home);
	return (ret);
}

static int	chdir_to_arg(t_list *token_list, char *cwd, int fd)
{
	int				ret;
	t_token *const	arg = token_list->next->content;
	const t_bool	chdir_to_oldpwd = (ft_strcmp(arg->value, "-") == 0);

	ret = 0;
	if (convert_path(&arg->value) == FALSE)
	{
		ret = 1 << 16;
		if (chdir_to_oldpwd)
			print_err(1, "cd", NULL, "OLDPWD not set");
		else
			print_err(1, "cd", NULL, EXIST_ERR);
	}
	else if (arg->value == NULL || chdir(arg->value) != 0)
		ret = errno;
	else if (chdir_to_oldpwd)
		ft_putendl_fd(arg->value, fd);
	set_path_env(cwd, arg->value);
	return (ret);
}

static t_bool	set_path_env(char *oldpwd, char *pwd)
{
	char *const	old_path = ft_strjoin("OLDPWD=", oldpwd);
	char *const	cur_path = ft_strjoin("PWD=", pwd);

	export(old_path);
	export(cur_path);
	free(old_path);
	free(cur_path);
	return (TRUE);
}
