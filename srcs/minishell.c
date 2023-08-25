/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:28 by younhwan          #+#    #+#             */
/*   Updated: 2023/03/08 12:50:37 by younhwan         ###   ########.fr       */
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
#include "../libs/libreadline/include/readline/readline.h"
#include "../libs/libreadline/include/readline/history.h"

static t_bool	init_minishell(int argc, char **argv, char **envp);
static t_bool	set_var(void);
static t_bool	execute_cmd_line(char **line);
static t_bool	print_minishell(void);

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	if (init_minishell(argc, argv, envp) == FALSE)
		return (print_err(2, argv[1], NULL, strerror(2)));
	while (TRUE)
	{
		set_var();
		line = readline("minishell-1.0$ ");
		if (line == NULL)
		{
			ft_putstr_fd("\033[1A", 1);
			ft_putstr_fd("\033[14C", 1);
			ft_putstr_fd(" exit\n", 1);
			exit(0);
		}
		add_history(line);
		execute_cmd_line(&line);
		free(line);
	}
	return (0);
}

static t_bool	init_minishell(int argc, char **argv, char **envp)
{
	g_var = ft_calloc(sizeof(t_var), 1, "");
	if (1 < argc && access(argv[1], F_OK) == -1)
		return (FALSE);
	print_minishell();
	init_termios();
	init_env_list(argc, argv, envp);
	g_var->old_fd[0] = dup(STDIN_FILENO);
	g_var->old_fd[1] = dup(STDOUT_FILENO);
	return (TRUE);
}

static t_bool	set_var(void)
{
	ft_lstclear(&g_var->token_list, del_token);
	ft_lstclear(&g_var->cmd_list, del_cmd);
	set_subsystem();
	dup2(g_var->old_fd[0], STDIN_FILENO);
	dup2(g_var->old_fd[1], STDOUT_FILENO);
	return (TRUE);
}

static t_bool	execute_cmd_line(char **line)
{
	t_bool	result;

	result = FALSE;
	if (lexer(line) == FALSE || \
		g_var->token_list == NULL || \
		parsing() == FALSE || \
		execute() == FALSE)
		result = TRUE;
	if (256 <= g_var->exit_status && g_var->exit_status % 256 != 0x7f)
		g_var->exit_status >>= 8;
	else if (result && 0 < g_var->exit_status && g_var->exit_status < 128)
		g_var->exit_status += 128;
	return (TRUE);
}

static t_bool	print_minishell(void)
{
	char *const	tty_name = ttyname(STDOUT_FILENO);

	ft_putstr_fd("███╗   ███╗██╗███╗   ██╗██╗", 1);
	ft_putendl_fd("███████╗██╗  ██╗███████╗██╗     ██╗     ", 1);
	ft_putstr_fd("████╗ ████║██║████╗  ██║██", 1);
	ft_putendl_fd("║██╔════╝██║  ██║██╔════╝██║     ██║     ", 1);
	ft_putstr_fd("██╔████╔██║██║██╔██╗ ██║██║", 1);
	ft_putendl_fd("███████╗███████║█████╗  ██║     ██║     ", 1);
	ft_putstr_fd("██║╚██╔╝██║██║██║╚██╗██║██║", 1);
	ft_putendl_fd("╚════██║██╔══██║██╔══╝  ██║     ██║     ", 1);
	ft_putstr_fd("██║ ╚═╝ ██║██║██║ ╚████║██║", 1);
	ft_putendl_fd("███████║██║  ██║███████╗███████╗███████╗", 1);
	ft_putstr_fd("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝", 1);
	ft_putstr_fd("╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝", 1);
	if (tty_name != NULL)
	{
		ft_putstr_fd("   on ", STDOUT_FILENO);
		ft_putstr_fd(tty_name, STDOUT_FILENO);
		free(tty_name);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (TRUE);
}
