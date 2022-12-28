#include "../../incs/builtin.h"
#include <errno.h>
#include <string.h>

int			builtin_cd(t_list *token_list, int fd);
static char	*get_home(void);

int	builtin_cd(t_list *token_list, int fd)
{
	char	*home;
	char	*path;

	home = get_home();
	path = NULL;
	if (token_list->next == NULL)
	{
		if (home == NULL || chdir(home) != 0)
			print_err(errno, "cd", NULL, strerror(errno));
	}
	else
	{
		if (((t_token *)token_list->next->content)->value[0] == '~')
			path = ft_strjoin(home,
					((t_token *)token_list->next->content)->value + 1);
		else
			path = ft_strdup(((t_token *)token_list->next->content)->value);
		if (chdir(path) != 0)
			print_err(errno, "cd",
				((t_token *)token_list->next->content)->value, strerror(errno));
		free(path);
	}
	fd = 0;
	free(home);
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
