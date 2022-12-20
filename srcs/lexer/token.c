#include "../../incs/lexer.h"
#include <stdlib.h>

t_token	*init_token(void);
t_token	*init_meta_token(const char *line, size_t *idx);
void	del_token(void *content);

t_token	*init_token(void)
{
	t_token	*ret;

	ret = (t_token *) ft_calloc(sizeof(t_token), 1, "Fail to init token");
	ret->type = T_WORD;
	ret->value = ft_strdup("");
	return (ret);
}

t_token	*init_meta_token(const char *line, size_t *idx)
{
	t_token *const	ret = init_token();

	if (line[*idx] == '|')
		ret->type = T_PIPE;
	else if (line[*idx] == '$')
		ret->type = T_WORD;
	else if (line[*idx] == '>' || line[*idx] == '<')
		ret->type = T_REDIRECT;
	else if (line[*idx] == '\'')
		ret->type = T_SINGLE_QUOTE;
	else if (line[*idx] == '"')
		ret->type = T_DOUBLE_QUOTE;
	ret->value = ft_strjoin(ret->value, ft_substr(line, *idx, 1));
	if (ret->type == T_REDIRECT && line[*idx] == line[*idx + 1])
		ret->value = ft_strjoin(ret->value, ft_substr(line, ++(*idx), 1));
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
