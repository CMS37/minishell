#include "../../incs/subsystem.h"
#include "../../libs/libft/incs/libft.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

t_bool	init_signal(void);
void	signal_handler(int sig);

t_bool	init_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	return (TRUE);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT) // Ctrl + C
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", STDOUT_FILENO);
		rl_redisplay();
	}
	return ;
}
