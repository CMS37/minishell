#ifndef LEXER_H
# define LEXER_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

# define TOKEN_ERR_MSG "Error: Fail to tokenize"

// tokenizer.c
t_list	*tokenize(const char *line);

// token.c
t_token	*init_token(void);
t_token	*init_meta_token(const char *line, size_t *idx);
void	del_token(void *content);

#endif