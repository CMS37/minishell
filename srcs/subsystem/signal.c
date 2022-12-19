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
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("minishell-1.0$ ", STDOUT_FILENO);
	}
	return ;
}
