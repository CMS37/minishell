/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:07 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 20:00:59 by younhwan         ###   ########.fr       */
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
static t_bool	set_oldpwd(char *oldpwd);
static t_bool	set_pwd(char *pwd);

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
		return (print_err(errno, "cd", arg->value, strerror(errno)));
	}
	path = arg->value;
	if (path == NULL || chdir(path) != 0)
		print_err(errno, "cd", arg->value, strerror(errno));
	if (set_oldpwd(oldpwd) == FALSE || set_pwd(path) == FALSE)
		print_err(errno, "cd", arg->value, strerror(errno));
	return (g_var->exit_status);
}

static int	chdir_to_home(char *oldpwd)
{
	char *const	home = home_dir();
	int			ret;

	ret = 0;
	if (home == NULL || chdir(home) != 0)
		ret = errno;
	else if (set_oldpwd(oldpwd) == FALSE || set_pwd(home) == FALSE)
		ret = errno;
	if (home != NULL)
		free(home);
	if (ret != 0)
		print_err(ret, "cd", NULL, strerror(ret));
	return (set_exit_status(ret));
}

static t_bool	set_oldpwd(char *oldpwd)
{
	t_list	*env;
	char	*path;

	env = get_env("OLDPWD");
	if (env == NULL)
		return (FALSE);
	path = ft_strjoin("OLDPWD=", oldpwd);
	replace_value(env, path);
	free(path);
	free(oldpwd);
	return (TRUE);
}

static t_bool	set_pwd(char *pwd)
{
	t_list		*env;
	char		*path;

	env = get_env("PWD");
	if (env == NULL)
		return (FALSE);
	path = ft_strjoin("PWD=", pwd);
	replace_value(env, path);
	free(path);
	return (TRUE);
}
