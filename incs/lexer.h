#ifndef LEXER_H
# define LEXER_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

static const char	*meta[] = {
	">",
	"<",
	">>",
	"<<",
	"|",
	"$",
	"\'",
	"\""
};

// tokenizer.c
t_bool		is_ifs(int c);
t_bool		is_meta(int c);

#endif