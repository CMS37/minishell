#include "../../libs/libft/incs/libft.h"
#include "../../incs/lexer.h"
#include <stdlib.h>

t_token	*init_token(void);
void	del_token(void *content);

t_token	*init_token(void)
{
	t_token	*ret;

	ret = ft_calloc(sizeof(t_token), 1, "Fail to init token");
	ret->type = T_WORD;
	ret->value = ft_strdup("");
	return (ret);
}

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *) content;
	free(token->value);
	free(token);
	return ;
}
