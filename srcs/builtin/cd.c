#include "../../incs/builtin.h"
#include "../../incs/lexer.h"
#include "../../incs/utils.h"
#include <errno.h>
#include <string.h>

int				builtin_cd(t_list *token_list, int fd);
static t_bool	chdir_to_home(char *home, char *oldpwd);
static t_bool	set_path_env(char *oldpwd);

int	builtin_cd(t_list *token_list, int fd)
{
	char *const		oldpwd = getcwd(NULL, 0);
	t_token *const	arg = token_list->next->content;
	char			*path;

	(void) fd;
	if (oldpwd == NULL)
		return (print_err(errno, "cd", NULL, strerror(errno)));
	if (ft_lstsize(token_list) == 1 && chdir_to_home(home_dir(), oldpwd))
		return (g_var->exit_status);
	else if (ft_lstsize(token_list) == 1)
		return (print_err(errno, "cd", NULL, strerror(errno)));
	if (ft_strchr(arg->value, '/') != NULL)
		path = convert_relative_path_to_absolute_path(arg->value);
	else if (arg->value[0] == '\0')
		path = oldpwd;
	else
		path = ft_strdup(arg->value);
	if (path == NULL || chdir(path) != 0)
		print_err(errno, "cd", arg->value, strerror(errno));
	else
		set_path_env(oldpwd);
	if (path != NULL)
		free(path);
	return (g_var->exit_status);
}

static t_bool	chdir_to_home(char *home, char *oldpwd)
{
	t_bool	ret;

	ret = TRUE;
	if (home == NULL || chdir(home) != 0)
		ret = FALSE;
	else if (set_path_env(oldpwd) == FALSE)
		ret = FALSE;
	if (home != NULL)
		free(home);
	free(oldpwd);
	return (ret);
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
