#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

t_bool		set_fd_in_redir(t_list *cmd);
static int	get_fd(t_list *cmd);
int			open_file(const char *file, t_open_flag flag);

t_bool	set_fd_in_redir(t_list *cmd)
{
	int		fd;

	while (cmd)
	{
		fd = get_fd(cmd);
		if (fd != -1)
		{
			if (ft_strcmp(((t_token *) cmd->content)->value, "<") == 0)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		cmd = cmd->next;
	}
	return (TRUE);
}

static int	get_fd(t_list *cmd)
{
	int		ret;
	t_token	*cur;
	t_token	*next;

	ret = -1;
	cur = cmd->content;
	next = NULL;
	if (cmd->next != NULL)
		next = cmd->next->content;
	if (ft_strcmp(cur->value, "<") == 0)
		ret = open_file(next->value, FILE_IN);
	else if (ft_strcmp(cur->value, ">") == 0)
		ret = open_file(next->value, FILE_OUT_TRUNC);
	else if (ft_strcmp(cur->value, ">>") == 0)
		ret = open_file(next->value, FILE_OUT_APPEND);
	return (ret);
}

int	open_file(const char *file, t_open_flag flag)
{
	int	fd;

	fd = 0;
	if (flag == HERE_DOC)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (flag == FILE_OUT_TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == FILE_IN)
		fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
	{
		if (flag == HERE_DOC || flag == FILE_OUT_TRUNC)
			perror("\033[31mError");
		if (flag == FILE_OUT_TRUNC)
			exit(EXIT_FAILURE);
		if (flag == FILE_IN)
		{
			ft_putstr_fd("\033[31mError: No such file or directory: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd("\033[m\n", 2);
		}	
	}
	return (fd);
}
