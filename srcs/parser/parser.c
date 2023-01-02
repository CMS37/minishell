/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:02 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 15:20:55 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"
#include "../../incs/utils.h"
#include "../../incs/structs.h"
#include <errno.h>
#include <string.h>

t_bool	parsing(void);

t_bool	parsing(void)
{
	if (g_var->token_list == NULL)
		return (FALSE);
	if (syntax_err_occurred())
	{
		if (g_var->exit_status == 258)
			return (print_err(258, NULL, NULL, SYNTAX_ERR) == 0);
		return (print_err(errno, NULL, NULL, strerror(errno)) == 0);
	}
	create_cmd_list();
	return (TRUE);
}

/*

check_word.c

t_list *check_word_type(t_list *list)
{
	t_list	*tmp;
	t_token	*token;
	// int		i;
	
	tmp = list;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		if (token->type == T_WORD)
		{
			if (find_path(token->value) == NULL) // is not command
				;
		}
		tmp = tmp->next;
	}
	return (list);
}
*/