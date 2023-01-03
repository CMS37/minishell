/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsystem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:56:59 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 14:57:00 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSYSTEM_H
# define SUBSYSTEM_H

# include "../libs/libft/incs/libft.h"

// signal.c
t_bool	init_signal(void);
void	signal_handler(int sig);
void	child_signal_handler(int sig);

// termios.c
t_bool	init_termios(void);

#endif