#include "../../libs/libft/incs/libft.h"
#include "../../incs/builtin.h"
#include "../../incs/execute.h"
#include "../../incs/subsystem.h"
#include "../../incs/utils.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void			execute_extern(t_list *token_list);
static char		**list_to_arr(t_list *token_list);
static char		*find_path(const char *cmd);
static char		*get_absolute_path(const char *cmd);	
static t_bool	free_paths(char **paths);

void	execute_extern(t_list *token_list)
{
	char **const	cmd = list_to_arr(token_list);
	char *const		path = find_path(cmd[0]);

	if (path == NULL)
		exit(print_err(127, cmd[0], NULL, CMD_ERR));
	set_exit_status(0);
	if (execve(path, cmd, ft_getenv()) == -1)
		exit(print_err(errno, cmd[0], NULL, strerror(errno)));
	ft_putendl_fd("This is easter egg!!", 2);
}

static char	**list_to_arr(t_list *token_list)
{
	const size_t	sz = ft_lstsize(token_list);
	char **const	ret = ft_calloc(sizeof(char *), sz + 1, "");
	size_t			i;

	i = 0;
	while (i < sz)
	{
		ret[i] = ft_strdup(((t_token *) token_list->content)->value);
		token_list = token_list->next;
		i++;
	}
	return (ret);
}

static char	*find_path(const char *cmd)
{
	char	*ret;
	char	**paths;
	t_list	*tmp;
	size_t	i;

	if (*cmd == '/' || *cmd == '~' || *cmd == '.')
		return (get_absolute_path(cmd));
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

static char	*get_absolute_path(const char *cmd)
{
	char	*ret;

	ret = convert_relative_path_to_absolute_path(cmd);
	if (ret == NULL)
		return (NULL);
	if (access(ret, X_OK) == 0)
		return (ret);
	free(ret);
	return (NULL);
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
