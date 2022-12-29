#include "../../libs/libft/incs/libft.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/subsystem.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int	builtin_pwd(t_list *token_list, int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (print_err(errno, "pwd", NULL, strerror(errno)));
	ft_putendl_fd(pwd, fd);
	free(pwd);
	(void) token_list;
	return (g_var->exit_status);
}
