#include "../../incs/execute.h"
#include "../../incs/builtin.h"
#include <unistd.h>

t_bool	is_builtin(t_list *cmd);
t_bool	execute_builtin(t_list *cmd);

t_bool	is_builtin(t_list *cmd)
{
	t_token	*token;

	while (cmd)
	{
		token = (t_token *) cmd->content;
		if (ft_strcmp(token->value, "env") == 0)
			return (TRUE);
		else if (ft_strcmp(token->value, "export") == 0)
			return (TRUE);
		else if (ft_strcmp(token->value, "pwd") == 0)
			return (TRUE);
		cmd = cmd->next;
	}
	return (FALSE);
}

t_bool	execute_builtin(t_list *cmd)
{
	t_token	*token;

	while (cmd)
	{
		token = (t_token *) cmd->content;
		if (ft_strcmp(token->value, "env") == 0)
			builtin_env(STDOUT_FILENO);
		else if (ft_strcmp(token->value, "export") == 0)
			builtin_export(cmd->next);
		else if (ft_strcmp(token->value, "pwd") == 0)
			builtin_pwd(STDOUT_FILENO);
		cmd = cmd->next;
	}
	return (FALSE);
}
