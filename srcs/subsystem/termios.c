/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:19 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 21:11:15 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/subsystem.h"
#include "../../incs/structs.h"
#include <stdio.h>
#include <unistd.h>

t_bool	init_termios(void);
t_bool	set_termios(void);
t_bool	reset_termios(void);

t_bool	init_termios(void)
{
	tcgetattr(STDOUT_FILENO, &(g_var->old_termios_stdout));
	tcgetattr(STDOUT_FILENO, &(g_var->new_termios_stdout));
	g_var->old_termios_stdout.c_lflag |= ECHOCTL;
	g_var->new_termios_stdout.c_lflag &= ~(ECHOCTL);
	return (TRUE);
}

t_bool	set_termios(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &(g_var->new_termios_stdout));
	return (TRUE);
}

t_bool	reset_termios(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &(g_var->old_termios_stdout));
	return (TRUE);
}
