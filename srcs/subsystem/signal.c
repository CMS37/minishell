/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:12 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 16:31:43 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/subsystem.h"
#include "../../incs/builtin.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>

t_bool		set_signal(void);
t_bool		unset_signal(int pid);
static void	handle_custom_signal(int sig);
static void	handle_default_signal_in_parent(int sig);

t_bool	set_signal(void)
{
	signal(SIGINT, handle_custom_signal);
	signal(SIGQUIT, SIG_IGN);
	return (TRUE);
}

t_bool	unset_signal(int pid)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, handle_default_signal_in_parent);
		signal(SIGQUIT, handle_default_signal_in_parent);
	}
	return (TRUE);
}

static void	handle_custom_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	return ;
}

static void	handle_default_signal_in_parent(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");
	return ;
}
