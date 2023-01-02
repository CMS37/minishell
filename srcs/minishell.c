/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:28 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 23:32:10 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/incs/libft.h"
#include "../incs/structs.h"
#include "../incs/subsystem.h"
#include "../incs/lexer.h"
#include "../incs/parser.h"
#include "../incs/execute.h"
#include "../incs/builtin.h"
#include "../incs/utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

// "'"'
// 서브쉘 시그널 중복 처리
// 

static t_bool	init_minishell(int argc, char **argv, char **envp);
static t_bool	init_var(void);
static t_bool	execute_cmd_line(const char *line);
static void		exit_minishell(void);

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	if (init_minishell(argc, argv, envp) == FALSE)
		return (print_err(2, argv[1], NULL, strerror(2)));
	while (TRUE)
	{
		line = readline("minishell-1.0$ ");
		if (line == NULL)
			exit_minishell();
		add_history(line);
		execute_cmd_line(line);
		free(line);
	}
	return (0);
}

static t_bool	init_minishell(int argc, char **argv, char **envp)
{
	g_var = ft_calloc(sizeof(t_var), 1, "");
	if (1 < argc && access(argv[1], F_OK) == -1)
		return (FALSE);
	init_var();
	init_termios();
	init_signal();
	init_env_list(argc, argv, envp);
	g_var->old_fd[0] = dup(STDIN_FILENO);
	g_var->old_fd[1] = dup(STDOUT_FILENO);
	return (TRUE);
}

static t_bool	init_var(void)
{
	ft_lstclear(&g_var->token_list, del_token);
	ft_lstclear(&g_var->cmd_list, del_cmd);
	g_var->here_doc_cnt = 0;
	return (TRUE);
}

static t_bool	execute_cmd_line(const char *line)
{
	init_var();
	if (lexer(line) == FALSE || g_var->token_list == NULL)
		return (FALSE);
	if (parsing() == FALSE)
		return (FALSE);
	execute();
	dup2(g_var->old_fd[0], STDIN_FILENO);
	dup2(g_var->old_fd[1], STDOUT_FILENO);
	return (TRUE);
}

static void	exit_minishell(void)
{
	ft_putstr_fd("\033[1A", 1);
	ft_putstr_fd("\033[14C", 1);
	ft_putstr_fd(" exit\n", 1);
	exit(0);
}
