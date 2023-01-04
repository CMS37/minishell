/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-cho <min-cho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:09 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 14:16:46 by min-cho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <stdlib.h>

int	builtin_echo(t_list *token_list, int fd);
static	t_bool check_n_flag(t_list **list);

int	builtin_echo(t_list *token_list, int fd)
{
	t_token	*token;
	t_bool	n_flag;

	if (token_list->next == NULL)
	{
		ft_putstr_fd("\n", fd);
		return (g_var->exit_status);
	}
	token_list = token_list->next;
	n_flag = check_n_flag(&token_list);
	token = token_list->content;
	// if (n_flag == TRUE)
	// 	token_list = token_list->next;
	while (token_list)
	{
		token = token_list->content;
		ft_putstr_fd(token->value, fd);
		if (token_list->next != NULL)
			ft_putstr_fd(" ", fd);
		token_list = token_list->next;
	}
	if (n_flag == FALSE)
		ft_putstr_fd("\n", fd);
	return (g_var->exit_status);
}

static	t_bool check_n_flag(t_list **list)
{
	t_token *token;
	int		flag;

	flag = FALSE;
	token = (*list)->content;
	while (ft_strncmp(token->value, "-n", 2) == 0)
	{
		if (ft_strlen(token->value) != 2)
		{
			while (1)
			{
				
			}
		}
		flag = TRUE;
		if ((*list)->next == NULL)
			break ;
		(*list) = (*list)->next;
		token = (*list)->content;
	}
	return (flag);
}