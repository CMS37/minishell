#include "../incs/minishell.h"
#include "../libs/libft/incs/libft.h"
#include <stdlib.h>
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	while (TRUE)
	{
		line = readline("minishell-1.0$ ");
		if (line == NULL)
			exit(EXIT_FAILURE);
		if (ft_strncmp(line, "exit", 4) == 0)
			break ;
		free(line);
	}
	free(line);
	
	(void) argc;
	(void) argv;
	(void) envp;
	return (0);
}
