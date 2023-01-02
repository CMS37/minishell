/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err_occurred.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:08 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 15:25:23 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"
#include "../../incs/builtin.h"
#include "../../incs/utils.h"
#include "../../incs/structs.h"

t_bool			syntax_err_occurred(void);
static t_bool	is_err(t_list *cur);

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
			if (here_doc(tmp->content) == FALSE)
				return (TRUE);
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
