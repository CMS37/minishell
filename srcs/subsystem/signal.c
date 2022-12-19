#include "../../incs/subsystem.h"
#include "../../libs/libft/incs/libft.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void sig_handler(int sig);

void sig_handler(int sig)
{
	if (sig == SIGINT) // Ctrl + C
	{
		ft_putstr_fd("minishell-1.0$ \n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", STDOUT_FILENO);
		rl_redisplay();
	}
	else if (sig == SIGQUIT) // Ctrl + '\'
	{
		;
	}
	return ;
}
