#include "../../libs/libft/incs/libft.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <unistd.h>

t_bool	init_env_list(char **envp);
int		builtin_env(t_list *token_list, int fd);

t_bool	init_env_list(char **envp)
{
	while (*envp != NULL)
		ft_lstadd_back(&g_var->env_list, ft_lstnew(ft_strdup(*envp++)));
	return (TRUE);
}

int	builtin_env(t_list *token_list, int fd)
{
	t_list	*cur_list;
	char	*cur_env;

	cur_list = g_var->env_list;
	while (cur_list != NULL)
	{
		cur_env = (char *) cur_list->content;
		ft_putendl_fd(cur_env, fd);
		cur_list = cur_list->next;
	}
	(void) token_list;
	return (g_var->exit_status);
}
