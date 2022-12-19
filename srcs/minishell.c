#include "../incs/minishell.h"
#include "../libs/libft/incs/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

t_var	*g_var;

static t_bool	init_minishell(void);
static t_bool	init_var(void);

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	g_var = NULL;
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

static t_bool	init_minishell(void)
{
	init_var();
	init_termios(g_var);
	init_signal();
	return (TRUE);
}

static t_bool	init_var(void)
{
	g_var = ft_calloc(sizeof(t_var), 1, "Failed to malloc at g_var");
	if (g_var == NULL)
		return (FALSE);
	return (TRUE);
}
