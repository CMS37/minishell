#include "../incs/minishell.h"
#include "../libs/ft_printf/includes/ft_printf.h"
#include "../libs/get_next_line/includes/get_next_line.h"
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	while (TRUE)
	{
		ft_putstr_fd("minishell-1.0$ ", STDOUT_FILENO);
		cmd = get_next_line(STDIN_FILENO);
		if (cmd == NULL)
			exit(EXIT_FAILURE);
		if (ft_strncmp(cmd, "exit", 4) == 0)
			break ;
		free(cmd);
	}
	free(cmd);
	
	(void) argc;
	(void) argv;
	(void) envp;
	return (0);
}
