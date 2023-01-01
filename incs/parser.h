#ifndef PARSER_H
# define PARSER_H

#include "../libs/libft/incs/libft.h"

// parser.c
t_bool	parsing(void);

// create_cmd_list.c
t_bool	create_cmd_list(void);
void	del_cmd(void *cmd);

// here_docs.c
t_bool	here_docs(void);

//syntax_err.c
t_bool	syntax_err_occurred(void);

#endif