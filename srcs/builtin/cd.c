#include "../../incs/builtin.h"
#include <errno.h>
#include <string.h>

int				builtin_cd(t_list *token_list, int fd);
static char		*get_home(void);
static t_bool	free_paths(char *home, char *path);
static int		chdir_to_home(char *home);

int	builtin_cd(t_list *token_list, int fd)
{
	char	*home;
	char	*path;
	t_token	*arg;

	(void) fd;
	home = get_home();
	if (ft_lstsize(token_list) == 1)
		return (chdir_to_home(home));
	arg = token_list->next->content;
	if (arg->value[0] == '~')
		path = ft_strjoin(home, arg->value + 1);
	else
		path = ft_strdup(arg->value);
	if ((path == NULL || chdir(path) != 0) && free_paths(home, path))
		return (print_err(errno, "cd", arg->value, strerror(errno)));
	free_paths(home, path);
	return (g_var->exit_status);
}

static char	*get_home(void)
{
	char	*res;
	char	*home;
	t_list	*tmp;

	tmp = g_var->env_list;
	while (tmp)
	{
		home = (char *) tmp->content;
		if (ft_strnstr(home, "HOME=", 5) != 0)
		{
			res = ft_strdup(home + 5);
			return (res);
		}
		tmp = tmp->next;
	}
	res = NULL;
	return (res);
}

static t_bool	free_paths(char *home, char *path)
{
	if (home)
		free(home);
	if (path)
		free(path);
	return (TRUE);
}

static int	chdir_to_home(char *home)
{
	if ((home == NULL || chdir(home) != 0) && free_paths(home, NULL))
		return (print_err(errno, "cd", NULL, strerror(errno)));
	free_paths(home, NULL);
	return (g_var->exit_status);
}
