#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include "../../incs/builtin.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int				execute(void);
static t_bool	child_process(t_list *cmd_list);

int	execute(void)
{
	here_docs();
	if (g_var->cmd_list->next == NULL && is_builtin(g_var->cmd_list))
		return (execute_builtin(g_var->cmd_list));
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
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		set_file_descriptors(cmd_list);
		if (is_builtin(cmd_list) && execute_builtin(cmd_list))
			exit(0);
		else
			execute_extern(cmd_list);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (cmd_list->next != NULL)
		child_process(cmd_list->next);
	waitpid(pid, NULL, 0);
	return (TRUE);
}
