#include "../../incs/subsystem.h"
#include <unistd.h>

t_bool	init_termios(t_var *var);
t_bool	reset_termios(t_var *var);

t_bool	init_termios(t_var *var)
{
	tcgetattr(STDOUT_FILENO, &(var->old_term));
	tcgetattr(STDOUT_FILENO, &(var->new_term));
	var->new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &(var->new_term));
	return (TRUE);
}

t_bool	reset_termios(t_var *var)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &(var->old_term));
	return (TRUE);
}
