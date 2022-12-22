#ifndef LEXER_H
# define LEXER_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// lexer.c
t_bool	lexer(const char *line);

// handle_quote.c
t_bool	handle_quote(t_token *token, const char **line);
t_bool	num_of_single_quote_is_odd(const char *line);
t_bool	num_of_double_quote_is_odd(const char *line);
t_bool	handle_single_quote(t_token *token, const char **line);
t_bool	handle_double_quote(t_token *token, const char **line);

// token.c
t_token	*init_token(void);
t_token	*init_meta_token(const char **line);
void	del_token(void *content);

// tokenizer.c
t_list	*tokenize(const char *line);

#endif