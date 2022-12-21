#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

t_bool	set_fd_in_redir(t_list *cmd);
int		open_file(const char *file, t_open_flag flag);

t_bool	set_fd_in_redir(t_list *cmd)
{
	int		fd;

	while (cmd)
	{
		fd = -1;
		if (ft_strcmp(((t_token *) cmd->content)->value, "<") == 0)
			fd = open_file(((t_token *) cmd->next->content)->value, FILE_IN);
		else if (ft_strcmp(((t_token *) cmd->content)->value, ">") == 0)
			fd = open_file(((t_token *) cmd->next->content)->value, FILE_OUT_TRUNC);
		else if (ft_strcmp(((t_token *) cmd->content)->value, ">>") == 0)
			fd = open_file(((t_token *) cmd->next->content)->value, FILE_OUT_APPEND);
		if (fd != -1)
		{
			if (ft_strcmp(((t_token *) cmd->content)->value, "<") == 0 && close(STDIN_FILENO))
				dup2(fd, STDIN_FILENO);
			else if (close(STDOUT_FILENO))
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		cmd = cmd->next;
	}
	return (TRUE);
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
