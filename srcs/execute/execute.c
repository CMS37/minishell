#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include "../../incs/builtin.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int				execute(void);
static t_bool	child_process(t_list *cmd);
static t_bool	set_fd_in_pipe(t_list *cmd, int *fd, t_bool is_child);

int	 execute(void)
{
	if (g_var->cmd_list == NULL)
		return (0);
	here_docs();
	if (g_var->cmd_list->next == NULL && is_builtin(g_var->cmd_list->content))
		return (execute_builtin(g_var->cmd_list->content));
	child_process(g_var->cmd_list);
	g_var->exit_status >>= 8;
	return (g_var->exit_status);
}

static t_bool	child_process(t_list *cmd)
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
		set_fd_in_pipe(cmd, fd, TRUE);
		if (set_fd_in_redir(cmd->content) == FALSE)
			exit(g_var->exit_status);
		if (is_builtin(cmd->content) && 0 <= execute_builtin(cmd->content))
			exit(g_var->exit_status);
		else
			execute_extern(cmd->content);
	}
	set_fd_in_pipe(cmd, fd, FALSE);
	if (cmd->next != NULL && child_process(cmd->next))
		waitpid(pid, NULL, 0);
	else
		waitpid(pid, &g_var->exit_status, 0);
	return (TRUE);
}

static t_bool	set_fd_in_pipe(t_list *cmd, int *fd, t_bool is_child)
{
	if (is_child)
	{
		close(fd[0]);
		if (cmd->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
		else
			dup2(g_var->old_fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (cmd->next != NULL)
			dup2(fd[0], STDIN_FILENO);
		else
			dup2(g_var->old_fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (TRUE);
}
