#include "../incs/minishell.h"
#include "../libs/libft/incs/libft.h"
#include <stdlib.h>
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	while (TRUE)
	{
		cmd = readline("minishell-1.0$ ");
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
