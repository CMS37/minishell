/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:09 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 20:17:41 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <stdlib.h>

int	builtin_echo(t_list *token_list, int fd);

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
	token = token_list->content;
	n_flag = (ft_strncmp(token->value, "-n", 2) == 0);
	if (n_flag == TRUE)
		token_list = token_list->next;
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
