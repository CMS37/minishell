#include "../../libs/libft/incs/libft.h"
#include "../../incs/execute.h"
#include "../../incs/builtin.h"
#include <unistd.h>

const static char	*g_builtin_list[] = {
	"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL
};

int static (*const	g_builtin_func[])(t_list *token_list, int fd) = {
	builtin_cd, builtin_echo, builtin_env, builtin_exit, 
	builtin_export, builtin_pwd, builtin_unset, NULL
};

t_bool	is_builtin(t_list *token_list);
t_bool	execute_builtin(t_list *token_list);

t_bool	is_builtin(t_list *token_list)
{
	char	**tmp;
	t_token	*token;

	tmp = (char **) g_builtin_list;
	token = (t_token *) token_list->content;
	while (*tmp)
	{
		if (ft_strcmp(token->value, *tmp) == 0)
			return (TRUE);
		tmp++;
	}
	return (FALSE);
}

t_bool	execute_builtin(t_list *token_list)
{
	t_token	*token;
	size_t	i;

	g_var->exit_status = 0;
	if (set_fd_in_redir(token_list) == FALSE)
		return (TRUE);
	token = (t_token *) token_list->content;
	i = 0;
	while (g_builtin_list[i] != NULL)
	{
		if (ft_strcmp(token->value, g_builtin_list[i]) == 0)
			return (g_builtin_func[i](token_list, 1));
		i++;
	}
	return (TRUE);
}
