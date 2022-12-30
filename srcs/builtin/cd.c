#include "../../incs/builtin.h"
#include "../../incs/lexer.h"
#include "../../incs/utils.h"
#include <errno.h>
#include <string.h>

int				builtin_cd(t_list *token_list, int fd);
static int		chdir_to_home(char *home);

int	builtin_cd(t_list *token_list, int fd)
{
	char	*path;
	t_token	*arg;

	(void) fd;
	if (ft_lstsize(token_list) == 1)
		return (chdir_to_home(home_dir()));
	arg = token_list->next->content;
	if (arg->value[0] == '/' || arg->value[0] == '~' || arg->value[0] == '.')
		path = convert_relative_path_to_absolute_path(arg->value);
	else
		path = ft_strdup(arg->value);
	if (path == NULL || chdir(path) != 0)
		print_err(errno, "cd", arg->value, strerror(errno));
	if (path != NULL)
		free(path);
	return (g_var->exit_status);
}

static int	chdir_to_home(char *home)
{
	if (home == NULL || chdir(home) != 0)
		print_err(errno, "cd", NULL, strerror(errno));
	if (home != NULL)
		free(home);
	return (g_var->exit_status);
}
