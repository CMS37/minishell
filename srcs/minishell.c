#include "../incs/minishell.h"
#include "../libs/libft/incs/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	signal(SIGINT, sig_handler); //ctrl+C 시그널 처리
	signal(SIGQUIT, SIG_IGN); // ctrl+\ 시그널 무시
	while (TRUE)
	{
		line = readline("minishell-1.0$ ");
		if (line == NULL)
			exit(EXIT_FAILURE);
		add_history(line);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		free(line);
	}
	free(line);
	
	(void) argc;
	(void) argv;
	(void) envp;
	return (0);
}

