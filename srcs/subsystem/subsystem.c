/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsystem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:31:29 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 21:11:20 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/subsystem.h"

t_bool	set_subsystem(void);
t_bool	unset_subsystem(int pid);

t_bool	set_subsystem(void)
{
	set_signal();
	set_termios();
	return (TRUE);
}

t_bool	unset_subsystem(int pid)
{
	unset_signal(pid);
	reset_termios();
	return (TRUE);
}
