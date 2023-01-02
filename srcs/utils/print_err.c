/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:26 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 15:51:29 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/subsystem.h"
#include "../../incs/builtin.h"

int	print_err(int status, char *cmd, char *arg, char *err_str);

int	print_err(int status, char *cmd, char *arg, char *err_str)
{
	ft_putstr_fd("minishell", 2);
	if (cmd != NULL && ft_putstr_fd(": ", 2))
		ft_putstr_fd(cmd, 2);
	if (arg != NULL && ft_putstr_fd(": ", 2))
	{
		if (ft_strlen(arg) == 1)
			ft_putchar_fd('`', 2);
		ft_putstr_fd(arg, 2);
		if (ft_strlen(arg) == 1)
			ft_putchar_fd('\'', 2);
	}
	if (err_str != NULL && ft_putstr_fd(": ", 2))
		ft_putstr_fd(err_str, 2);
	ft_putstr_fd("\n", 2);
	return (set_exit_status(status));
}
