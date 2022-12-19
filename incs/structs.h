#ifndef STRUCTS_H
# define STRUCTS_H

# include <termios.h>

typedef struct termios	t_termios;

typedef struct	s_var
{
	t_termios	old_term;
	t_termios	new_term;
}	t_var;

#endif