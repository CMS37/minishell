#ifndef PARSER_H
# define PARSER_H

#include "../libs/libft/incs/libft.h"


# define SYNTAX_ERR 258;
// parser.c
void	parsing(t_list *list);

// parser_utils.c
t_bool	is_unexpected_token(const char *token);
int		next_pipe(t_list *list);
int		all_pipe(t_list *list);
void	free_cmd(char **cmd);

//int	near_red(const char *s1);

#endif