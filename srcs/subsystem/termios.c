/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:19 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 14:58:30 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/subsystem.h"
#include "../../incs/structs.h"
#include <unistd.h>

t_bool	init_termios(void);
t_bool	reset_termios(void);

t_bool	init_termios(void)
{
	tcgetattr(STDOUT_FILENO, &(g_var->old_term));
	tcgetattr(STDOUT_FILENO, &(g_var->new_term));
	g_var->new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &(g_var->new_term));
	return (TRUE);
}

t_bool	reset_termios(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &(g_var->old_term));
	return (TRUE);
}
