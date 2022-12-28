#ifndef LEXER_H
# define LEXER_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// lexer.c
t_bool	lexer(const char *line);

// handle_env_var.c
t_bool	handle_env_var(t_token *token, const char **line);

// handle_quote.c
t_bool	handle_quote(t_token *token, const char **line);
t_bool	num_of_single_quote_is_odd(const char *line);
t_bool	num_of_double_quote_is_odd(const char *line);

// token.c
t_token	*init_token(void);
t_token	*init_meta_token(const char **line);
void	del_token(void *content);

// tokenizer.c
t_bool	tokenize(const char *line);
t_bool	is_ifs(int c);

#endif