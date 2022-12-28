#include "../../libs/libft/incs/libft.h"
#include "../../incs/lexer.h"
#include <stdlib.h>

t_token	*init_token(void);
t_token	*init_meta_token(const char **line);
void	del_token(void *content);

t_token	*init_token(void)
{
	t_token	*ret;

	ret = ft_calloc(sizeof(t_token), 1, "Fail to init token");
	ret->type = T_WORD;
	ret->value = ft_strdup("");
	return (ret);
}

t_token	*init_meta_token(const char **line)
{
	t_token *const	ret = init_token();

	if (**line == '|')
		ret->type = T_PIPE;
	else if (**line == '>' || **line == '<')
		ret->type = T_REDIRECT;
	ft_strncat(&ret->value, *line, 1);
	if (ret->type == T_REDIRECT && **line == *(*line + 1))
		ft_strncat(&ret->value, ++(*line), 1);
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
