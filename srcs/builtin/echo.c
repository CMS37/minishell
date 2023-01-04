/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:09 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 16:44:41 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <stdlib.h>

int				builtin_echo(t_list *token_list, int fd);
static t_bool	check_n_flag(t_token *token);

int	builtin_echo(t_list *token_list, int fd)
{
	t_bool	n_flag;

	if (token_list->next == NULL)
	{
		ft_putstr_fd("\n", fd);
		return (g_var->exit_status);
	}
	token_list = token_list->next;
	n_flag = FALSE;
	while (token_list)
	{
		if (check_n_flag(((t_token *) token_list->content)) == TRUE)
			n_flag = TRUE;
		else
		{
			ft_putstr_fd(((t_token *) token_list->content)->value, fd);
			if (token_list->next != NULL)
				ft_putstr_fd(" ", fd);
		}
		token_list = token_list->next;
	}
	if (n_flag == FALSE)
		ft_putstr_fd("\n", fd);
	return (g_var->exit_status);
}

static t_bool	check_n_flag(t_token *token)
{
	size_t	i;

	if (ft_strncmp(token->value, "-n", 2) != 0)
		return (FALSE);
	i = 2;
	while (token->value[i])
	{
		if (token->value[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
