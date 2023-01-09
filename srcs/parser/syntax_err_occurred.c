/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err_occurred.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:08 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/10 01:02:41 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"
#include "../../incs/builtin.h"
#include "../../incs/utils.h"
#include "../../incs/structs.h"
#include "../../incs/subsystem.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

t_bool			syntax_err_occurred(void);
static t_bool	is_err(t_list *cur);
static int		child_process_to_heredoc(t_token *token);

t_bool	syntax_err_occurred(void)
{
	t_list	*tmp;

	tmp = g_var->token_list;
	if (((t_token *) tmp->content)->type == T_PIPE)
		return (set_exit_status(258));
	while (tmp)
	{
		if (is_err(tmp))
			return (TRUE);
		if (ft_strcmp(((t_token *) tmp->content)->value, "<<") == 0)
		{
			tmp = tmp->next;
			if (child_process_to_heredoc(tmp->content) != 0)
			{
				if (g_var->exit_status == 2)
					g_var->exit_status = 1;
				return (TRUE);
			}
		}
		tmp = tmp->next;
	}
	return (FALSE);
}

static t_bool	is_err(t_list *cur)
{
	t_token	*cur_t;
	t_token	*next_t;

	cur_t = (t_token *) cur->content;
	next_t = NULL;
	if (cur->next != NULL)
		next_t = (t_token *) cur->next->content;
	if (cur_t->type == T_PIPE
		&& (cur->next == NULL || next_t->type == T_PIPE))
		return (set_exit_status(258));
	if (cur_t->type == T_REDIRECT
		&& (next_t == NULL || next_t->type != T_WORD))
		return (set_exit_status(258));
	return (FALSE);
}

static int	child_process_to_heredoc(t_token *token)
{
	char *const	file_name = generate_file_name();
	char *const	end_flag = ft_strdup(token->value);
	pid_t		pid;
	int			exit_status;

	free(token->value);
	token->value = file_name;
	pid = fork();
	if (pid == -1)
	{
		free(end_flag);
		return (errno);
	}
	set_signal_while_heredoc(pid);
	if (pid == 0)
	{
		exit_status = 0;
		if (here_doc(token->value, end_flag) == FALSE)
			exit_status = errno;
		exit(exit_status);
	}
	free(end_flag);
	waitpid(pid, &g_var->exit_status, 0);
	return (g_var->exit_status);
}
