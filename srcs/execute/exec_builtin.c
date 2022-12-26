#include "../../incs/execute.h"
#include "../../incs/builtin.h"
#include <unistd.h>

t_bool	is_builtin(t_list *token_list);
t_bool	execute_builtin(t_list *token_list);

t_bool	is_builtin(t_list *token_list)
{
	t_token	*token;

	while (token_list)
	{
		token = (t_token *) token_list->content;
		if (ft_strcmp(token->value, "env") == 0)
			return (TRUE);
		else if (ft_strcmp(token->value, "export") == 0)
			return (TRUE);
		else if (ft_strcmp(token->value, "pwd") == 0)
			return (TRUE);
		token_list = token_list->next;
	}
	return (FALSE);
}

t_bool	execute_builtin(t_list *token_list)
{
	t_token	*token;

	while (token_list)
	{
		token = (t_token *) token_list->content;
		if (ft_strcmp(token->value, "env") == 0)
			builtin_env(STDOUT_FILENO);
		else if (ft_strcmp(token->value, "export") == 0)
			builtin_export(token_list->next);
		else if (ft_strcmp(token->value, "pwd") == 0)
			builtin_pwd(STDOUT_FILENO);
		token_list = token_list->next;
	}
	return (FALSE);
}
