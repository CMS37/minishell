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
	return (ret);
}

t_token	*init_meta_token(const char **line)
{
	t_token *const	ret = init_token();

	if (**line == '|')
		ret->type = T_PIPE;
	else if (**line == '>' || **line == '<')
		ret->type = T_REDIRECT;
	ft_strcat(ret->value, ft_substr(*line, 0, 1));
	if (ret->type == T_REDIRECT && **line == *(*line + 1))
		ft_strcat(ret->value, ft_substr(++(*line), 0, 1));
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
