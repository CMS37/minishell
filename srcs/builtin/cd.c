#include "../../incs/builtin.h"
#include <errno.h>
#include <string.h>

int			builtin_cd(t_list *token_list, int fd);
static char	*get_home(void);

int	builtin_cd(t_list *token_list, int fd)
{
	t_list	*tmp;
	char	*home;

	if (token_list->next == NULL)
	{
		home = get_home();
		if (home == NULL || chdir(home) != 0)
			print_err(1, "cd", NULL, "No home");
	}
	else
	{
		tmp = token_list->next;
		if (chdir(((t_token *)tmp->content)->value) != 0)
			print_err(1, "cd",
				((t_token *)tmp->content)->value, strerror(errno));
	}
	fd = 0;
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
