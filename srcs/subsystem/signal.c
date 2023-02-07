/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:12 by younhwan          #+#    #+#             */
/*   Updated: 2023/02/07 13:01:39 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/subsystem.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "../../libs/libreadline/include/readline/readline.h"

t_bool			set_signal(void);
t_bool			unset_signal(int pid);
t_bool			set_signal_while_heredoc(int pid);
static void		handle_custom_signal(int sig);
static void		unlink_and_exit(int sig);

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
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (TRUE);
}

static void	handle_custom_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_var->exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	return ;
}

t_bool	set_signal_while_heredoc(int pid)
{
	if (pid == 0)
		signal(SIGINT, unlink_and_exit);
	else
		signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (TRUE);
}

static void	unlink_and_exit(int sig)
{
	t_list	*tmp;

	tmp = g_var->token_list;
	while (tmp)
	{
		if (ft_strcmp(((t_token *) tmp->content)->value, "<<") == 0)
		{
			tmp = tmp->next;
			unlink(((t_token *) tmp->content)->value);
		}
		tmp = tmp->next;
	}
	exit(1);
	(void) sig;
}
