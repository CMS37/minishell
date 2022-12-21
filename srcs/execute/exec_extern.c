#include "../../incs/execute.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void			execute_extern(t_list *cur_cmd);
static char		*find_path(const char *cmd);
static t_bool	free_paths(char **paths);
static char		**envp_list_to_arr(void);

void	execute_extern(t_list *cur_cmd)
{
	char **const	cmd = list_to_arr(cur_cmd);
	char *const		path = find_path(cmd[0]);

	if (path == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd[0], STDERR_FILENO);
		exit(127);
	}
	if (execve(path, cmd, envp_list_to_arr()) == -1)
	{
		ft_putendl_fd("minishell: execve failed", STDERR_FILENO);
		perror("Error");
		exit(1);
	}
}

static char	*find_path(const char *cmd)
{
	char	*ret;
	char	**paths;
	t_list	*tmp;

	tmp = g_var->env_list;
	while(ft_strnstr(tmp->content, "PATH=", 5) == NULL)
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	paths = ft_split(tmp->content + 5, ':');
	while (*paths)
	{
		ret = ft_strjoin(*paths, "/");
		ret = ft_strjoin(ret, cmd);
		if (access(ret, X_OK) == 0 && free_paths(paths))
			return (ret);
		free(ret);
		paths++;
	}
	free_paths(paths);
	return (NULL);
}

static t_bool	free_paths(char **paths)
{
	while (*paths)
		free(*paths++);
	free(paths);
	return (TRUE);
}

static char		**envp_list_to_arr(void)
{
	char **const	ret = \
		(char **) ft_calloc(sizeof(char *), ft_lstsize(g_var->env_list) + 1, "");
	char 			**ret_tmp;
	t_list			*env_list_tmp;

	ret_tmp = ret;
	env_list_tmp = g_var->env_list;
	while (env_list_tmp)
	{
		*ret_tmp++ = ft_strdup(env_list_tmp->content);
		env_list_tmp = env_list_tmp->next;
	}
	return (ret);
}
