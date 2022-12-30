#ifndef LEXER_H
# define LEXER_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// lexer.c
t_bool	lexer(const char *line);

// expand.c
t_bool	handle_expand(t_token *token, const char **line);
t_bool	is_expand(int c);

// ifs.c
t_bool	is_ifs(int c);

// meta.c
t_bool	handle_meta(const char **line);
t_bool	is_meta(int c);
t_token	*init_meta_token(const char **line);

// quote.c
t_bool	handle_quote(t_token *token, const char **line);
t_bool	is_quote(int c);

// token.c
t_token	*init_token(void);
t_token	*clone_token(t_token *token);
void	del_token(void *content);

// tokenizer.c
t_bool	tokenize(const char *line);
t_bool	is_not_word(int c);

#endif