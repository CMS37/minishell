/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:15 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 16:23:36 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int				builtin_exit(t_list *token_list, int fd);
int				set_exit_status(int status);
static t_bool	is_num(const char *str);

int	builtin_exit(t_list *token_list, int fd)
{
	t_list		*tmp;
	t_token		*token;
	long long	i;

	tmp = token_list->next;
	ft_putendl_fd("exit", fd);
	if (tmp == NULL)
		exit(set_exit_status(0) >> 8);
	token = tmp->content;
	if (is_num(token->value) == FALSE)
		exit(print_err(255, "exit", token->value, NUMERIC_ERR) >> 8);
	if (tmp->next != NULL)
		return (print_err(1, "exit", NULL, ARG_ERR) >> 8);
	i = ft_atoll(token->value);
	if (i < INT_MIN || INT_MAX < i)
		exit(print_err(255, "exit", token->value, NUMERIC_ERR) >> 8);
	if (i < 0)
		i = (256 - ((i * -1) % 256));
	i = (i % 256);
	exit(set_exit_status(i) >> 8);
	return (g_var->exit_status);
}

int	set_exit_status(int status)
{
	g_var->exit_status = status << 8;
	return (g_var->exit_status);
}

static t_bool	is_num(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (str && *str)
	{
		if (('0' <= *str && *str <= '9') == FALSE)
			return (FALSE);
		str++;
	}
	return (TRUE);
}
