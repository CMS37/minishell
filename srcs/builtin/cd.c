#include "../../incs/builtin.h"
#include <errno.h>
#include <string.h>

int			builtin_cd(t_list *token_list, int fd);
static char	*get_home(void);

int	builtin_cd(t_list *token_list, int fd)
{
	t_list	*tmp;
	char	*home;
	char	*path;

	home = get_home();
	if (token_list->next == NULL)
	{
		if (home == NULL || chdir(home) != 0)
			print_err(errno, "cd", NULL, strerror(errno));
	}
	else
	{
		tmp = token_list->next;
		if (((t_token *)tmp->content)->value[0] == '~')
			path = ft_strjoin(home, ((t_token *)tmp->content)->value + 1);
		else
			path = ((t_token *)tmp->content)->value;
		if (chdir(path) != 0)
			print_err(errno, "cd",
				((t_token *)tmp->content)->value, strerror(errno));
	}
	fd = 0;
	free(home);
	free(path);
	return (0);
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
		if (ft_strnstr(home, "HOME", 4) != 0)
		{
			res = ft_strdup(home + 5);
			return (res);
		}
		tmp = tmp->next;
	}
	res = NULL;
	return (home);
}
