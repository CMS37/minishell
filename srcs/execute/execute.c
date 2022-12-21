#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include "../../incs/builtin.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int				execute(void);
static t_bool	child_process(t_list *cmd_list);
static t_bool	set_fd_in_pipe(t_list *cmd_list, int *fd, t_bool is_child);

int	execute(void)
{
	if (g_var->cmd_list == NULL)
		return (0);
	here_docs();
	if (g_var->cmd_list->next == NULL && is_builtin(g_var->cmd_list->content))
		return (execute_builtin(g_var->cmd_list->content));
	child_process(g_var->cmd_list);
	return (0);
}

static t_bool	child_process(t_list *cmd_list)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (FALSE);
	pid = fork();
	if (pid == -1)
		return (FALSE);
	if (pid == 0)
	{
		set_fd_in_pipe(cmd_list, fd, TRUE);
		set_fd_in_redir(cmd_list->content);
		if (is_builtin(cmd_list->content) && execute_builtin(cmd_list->content))
			exit(0);
		else
			execute_extern(cmd_list->content);
	}
	set_fd_in_pipe(cmd_list, fd, FALSE);
	if (cmd_list->next != NULL)
		child_process(cmd_list->next);
	waitpid(pid, NULL, 0);
	return (TRUE);
}

static t_bool	set_fd_in_pipe(t_list *cmd_list, int *fd, t_bool is_child)
{
	if (is_child)
	{
		close(fd[0]);
		if (cmd_list != g_var->cmd_list)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (cmd_list->next != NULL)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (TRUE);
}
