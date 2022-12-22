#ifndef PARSER_H
# define PARSER_H

#include "../libs/libft/incs/libft.h"
#include "lexer.h"
#include "structs.h"
#include "execute.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// parser.c
void	parsing(void);

//check_quotes.c
t_bool	check_quotes(t_list *tmp);

//syntax_err.c
t_bool	check_syntax_err(void);

//check_word.c
t_list *check_word_type(t_list *list);

// check_unexpected_token.c
void	check_unexpected_token(void);

// create_cmd_list.c
t_bool	create_cmd_list(void);

#endif