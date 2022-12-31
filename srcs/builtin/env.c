#include "../../libs/libft/incs/libft.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <unistd.h>

int		builtin_env(t_list *token_list, int fd);
t_bool	init_env_list(int argc, char **argv, char **envp);

int	builtin_env(t_list *token_list, int fd)
{
	t_list	*cur_list;
	char	*cur_env;

	cur_list = g_var->env_list;
	while (cur_list != NULL)
	{
		cur_env = (char *) cur_list->content;
		if (ft_strchr(cur_env, '=') != NULL)
			ft_putendl_fd(cur_env, fd);
		cur_list = cur_list->next;
	}
	(void) token_list;
	return (g_var->exit_status);
}

t_bool	init_env_list(int argc, char **argv, char **envp)
{
	int		shlvl;
	char	*c_shlvl;

	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "SHLVL", 5) == 0)
		{
			shlvl = ft_atoi(ft_strchr(*envp, '=') + 1) + 1;
			c_shlvl = ft_itoa(shlvl);
			ft_lstadd_back(&g_var->env_list,
				ft_lstnew(ft_strjoin("SHLVL=", c_shlvl)));
			free(c_shlvl);
			envp++;
			continue ;
		}
		ft_lstadd_back(&g_var->env_list, ft_lstnew(ft_strdup(*envp++)));
	}
	free(ft_lstlast(g_var->env_list)->content);
	ft_lstlast(g_var->env_list)->content = ft_strjoin("_=", argv[argc - 1]);
	return (TRUE);
}
