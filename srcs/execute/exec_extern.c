#include "../../libs/libft/incs/libft.h"
#include "../../incs/builtin.h"
#include "../../incs/execute.h"
#include "../../incs/subsystem.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void			execute_extern(t_list *token_list);
char			*find_path(const char *cmd);
static char		*find_relative_or_absolute_path(const char *cmd);
static t_bool	free_paths(char **paths);
static char		**envp_list_to_arr(void);

void	execute_extern(t_list *token_list)
{
	char **const	cmd = list_to_arr(token_list);
	char *const		path = find_path(cmd[0]);

	if (path == NULL)
	{
		if (ft_strnstr(cmd[0], "$?", 2) != 0)
			print_err(127, ft_itoa(g_var->exit_status), NULL, CMD_ERR);
		else
			print_err(127, cmd[0], NULL, CMD_ERR);
		exit(set_exit_status(127));
	}
	set_exit_status(0);
	if (execve(path, cmd, envp_list_to_arr()) == -1)
	{
		print_err(errno, cmd[0], NULL, strerror(errno));
		exit(set_exit_status(errno));
	}
}

char	*find_path(const char *cmd)
{
	char	*ret;
	char	**paths;
	t_list	*tmp;
	size_t	i;

	if (*cmd == '/' || *cmd == '.')
		return(find_relative_or_absolute_path(cmd));
	tmp = g_var->env_list;
	while (ft_strnstr(tmp->content, "PATH=", 5) == NULL)
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	paths = ft_split(tmp->content + 5, ':');
	i = 0;
	while (paths[i])
	{
		ret = ft_strjoin(paths[i], "/");
		ft_strcat(&ret, cmd);
		if (access(ret, X_OK) == 0 && free_paths(paths))
			return (ret);
		free(ret);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

static char	*find_relative_or_absolute_path(const char *cmd)
{
	char	*ret;

	if (*cmd == '/' && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	ret = getcwd(NULL, 0);
	if (ret == NULL)
		return (NULL);
	ft_strcat(&ret, cmd + 1);
	return (ret);
}

static t_bool	free_paths(char **paths)
{
	char	**tmp;

	if (paths == NULL)
		return (TRUE);
	tmp = paths;
	while (*tmp)
		free(*tmp++);
	free(paths);
	return (TRUE);
}

static char	**envp_list_to_arr(void)
{
	char **const	ret = (char **) ft_calloc(sizeof(char *),
			ft_lstsize(g_var->env_list) + 1, "");
	char			**ret_tmp;
	t_list			*env_list_tmp;

	ret_tmp = ret;
	env_list_tmp = g_var->env_list;
	while (env_list_tmp)
	{
		*ret_tmp++ = ft_strdup(env_list_tmp->content);
		env_list_tmp = env_list_tmp->next;
	}
	*ret_tmp = NULL;
	return (ret);
}
