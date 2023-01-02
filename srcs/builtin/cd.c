/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:07 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 14:57:08 by younhwan         ###   ########.fr       */
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
static t_bool	set_path_env(char *oldpwd);

int	builtin_cd(t_list *token_list, int fd)
{
	char *const		oldpwd = getcwd(NULL, 0);
	t_token *const	arg = token_list->next->content;
	char			*path;

	(void) fd;
	if (oldpwd == NULL)
		return (print_err(errno, "cd", NULL, strerror(errno)));
	if (ft_lstsize(token_list) == 1)
		return (chdir_to_home(oldpwd));
	if (convert_to_absolute_path(&arg->value) == FALSE)
	{
		free(oldpwd);
		return (print_err(errno, "cd", arg->value, strerror(errno)));
	}
	if (arg->value[0] == '\0')
		path = oldpwd;
	else
		path = arg->value;
	if (path == NULL || chdir(path) != 0)
		print_err(errno, "cd", arg->value, strerror(errno));
	else
		set_path_env(oldpwd);
	free(oldpwd);
	return (g_var->exit_status);
}

static int	chdir_to_home(char *oldpwd)
{
	char *const	home = home_dir();
	int			ret;

	ret = 0;
	if (home == NULL || chdir(home) != 0)
		ret = errno;
	else if (set_path_env(oldpwd) == FALSE)
		ret = errno;
	if (home != NULL)
		free(home);
	free(oldpwd);
	if (ret != 0)
		print_err(ret, "cd", NULL, strerror(ret));
	return (set_exit_status(ret));
}

static t_bool	set_path_env(char *oldpwd)
{
	t_list	*env;
	char	*path;
	char	*pwd;

	env = get_env("OLDPWD");
	if (env == NULL)
		return (FALSE);
	path = ft_strjoin("OLDPWD=", oldpwd);
	replace_value(env, path);
	free(path);
	env = get_env("PWD");
	if (env == NULL)
		return (FALSE);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (FALSE);
	path = ft_strjoin("PWD=", pwd);
	replace_value(env, path);
	free(path);
	return (TRUE);
}
