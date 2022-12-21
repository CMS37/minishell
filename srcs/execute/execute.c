#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include "../../incs/builtin.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		execute(void);
t_bool	is_builtin(t_list *cmd_list);
t_bool	execute_builtin(t_list *cmd_list);

int	execute(void)
{
	here_docs();
	if (g_var->cmd_list->next == NULL && is_builtin(g_var->cmd_list))
		return (execute_builtin(g_var->cmd_list));
	return (0);
}

t_bool	is_builtin(t_list *cmd_list)
{
	char	**tokens;

	tokens = cmd_list->content;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "env") == 0)
			return (TRUE);
		else if (ft_strcmp(*tokens, "pwd") == 0)
			return (TRUE);
		tokens++;
	}
	return (FALSE);
}

t_bool	execute_builtin(t_list *cmd_list)
{
	char	**tokens;

	set_file_descriptors(cmd_list);	
	tokens = cmd_list->content;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "env") == 0)
			builtin_env(STDOUT_FILENO);
		else if (ft_strcmp(*tokens, "pwd") == 0)
			builtin_pwd(STDOUT_FILENO);
		tokens++;
	}
	
	return (TRUE);
}
