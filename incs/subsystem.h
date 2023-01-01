#ifndef SUBSYSTEM_H
# define SUBSYSTEM_H

# include "../libs/libft/incs/libft.h"

// signal.c
t_bool	init_signal(void);
void	signal_handler(int sig);

// termios.c
t_bool	init_termios(void);

#endif