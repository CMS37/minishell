#ifndef PARSER_H
# define PARSER_H

#include "../libs/libft/incs/libft.h"

// parser.c
void	parsing(t_list *list);

// parser_utils.c
t_bool	is_unexpected_token(const char *token);
//int	near_red(const char *s1);

#endif