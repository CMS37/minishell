#include "../incs/libft.h"
#include <stdlib.h>

void	ft_exit_with_error(const char *str, int exit_flag)
{
	ft_putstr_fd("\033[31mError\033[0m\n", 2);
	if (str)
	{
		ft_putstr_fd("\033[31m", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\033[0m\n", 2);
	}
	exit(exit_flag);
}
