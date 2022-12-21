#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <stdlib.h>

int	builtin_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	ft_putendl_fd(pwd, fd);
	free(pwd);
	g_var->exit_status = 0;
	return (0);
}
