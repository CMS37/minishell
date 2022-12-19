#include "../incs/minishell.h"
#include "../libs/libft/incs/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

t_var	*var;

static t_bool	init_minishell();
static t_bool	init_var();

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	var = NULL;
	init_minishell();
	while (TRUE)
	{
		line = readline("minishell-1.0$ ");
		if (line == NULL)
		{
			printf("\033[1A");
            printf("\033[14C");
            printf(" exit\n");
            exit(-1);
		}
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

static t_bool	init_minishell()
{
	init_var();
	init_termios(var);
	signal(SIGINT, sig_handler);
	return (TRUE);
}

static t_bool	init_var()
{
	var = ft_calloc(sizeof(t_var), 1, "Failed to malloc at var");
	if (var == NULL)
		return (FALSE);
	return (TRUE);
}