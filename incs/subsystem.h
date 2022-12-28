#ifndef SUBSYSTEM_H
# define SUBSYSTEM_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

# define IDENTIFIER_ERR "not a valid identifier" //export에서 인자가 잘못올때
# define NUMERIC_ERR "numeric argument required" //exit 인자로 정수를넘는 숫자가오면
# define ARG_ERR "too many arguments" // exit에서 많은 인자가 올떄
# define CMD_ERR "Command not found" // input에 이상한 값오면

// signal.c
t_bool	init_signal(void);
void	signal_handler(int sig);

// termios.c
t_bool	init_termios(void);

//exit_status.c
t_bool	exit_status(char *cmd, char *value, char *err_str);
t_bool	set_exit_status(int status);

#endif