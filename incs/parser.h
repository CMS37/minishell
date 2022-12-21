#ifndef PARSER_H
# define PARSER_H

#include "../libs/libft/incs/libft.h"


# define SYNTAX_ERR 258;
// parser.c
void	parsing(t_list *list);

// check_unexpected_token.c
void	check_unexpected_token(t_list *list);

// create_cmd_list.c
t_bool	create_cmd_list(void);

#endif