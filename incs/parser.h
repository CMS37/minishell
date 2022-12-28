#ifndef PARSER_H
# define PARSER_H

#include "../libs/libft/incs/libft.h"
# include "subsystem.h"
# include "lexer.h"
# include "structs.h"
# include "execute.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

// parser.c
t_bool	parsing(void);

//syntax_err.c
t_bool	syntax_err_occurred(void);

// create_cmd_list.c
t_bool	create_cmd_list(void);

#endif