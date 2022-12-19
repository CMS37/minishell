/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-cho <min-cho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:03:06 by min-cho           #+#    #+#             */
/*   Updated: 2022/12/19 20:00:28 by min-cho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("minishell-1.0$ ", 0);
	}
}

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
			write(1, "exit\n", 6);
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
