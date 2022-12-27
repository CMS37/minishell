#include "../incs/minishell.h"
#include "../libs/libft/incs/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static t_bool	init_minishell(char **envp);
static t_bool	init_var(void);
static t_bool	execute_cmd_line(const char *line);
void			exit_minishell(void);

static t_bool	print_token_list(void);

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	
	(void) argc;
	(void) argv;
	init_minishell(envp);
	while (TRUE)
	{
		line = readline("minishell-1.0$ ");
		if (line == NULL)
			exit_minishell();
//		if (ft_strncmp(line, "exit", 4) == 0 && ft_putstr_fd("exit\n", 1))
//			break ;
		add_history(line);
		execute_cmd_line(line);
		free(line);
		printf("ERR_CODE : %d\n", g_var->exit_status); //test
	}
	free(line);
	return (0);
}

static t_bool	init_minishell(char **envp)
{
	init_var();
	init_termios();
	init_signal();
	init_env_list(envp);
	g_var->old_fd[0] = dup(STDIN_FILENO);
	g_var->old_fd[1] = dup(STDOUT_FILENO);
	g_var->old_fd[2] = dup(STDERR_FILENO);
	return (TRUE);
}

static t_bool	init_var(void)
{
	g_var = (t_var *) ft_calloc(sizeof(t_var), 1, "Failed to init var");
	if (g_var == NULL)
		return (FALSE);
	return (TRUE);
}

static t_bool	execute_cmd_line(const char *line)
{
	if (lexer(line) == FALSE || !g_var->token_list)
		return (FALSE);
	print_token_list();
	parsing();
	execute();
	close(STDERR_FILENO);
	dup2(g_var->old_fd[2], STDERR_FILENO);
	return (TRUE);
}

void	exit_minishell(void)
{
	printf("\033[1A");
	printf("\033[14C");
	printf(" exit\n");
	exit(0);
}

static t_bool	print_token_list(void)
{
	t_list	*cur_list;
	t_token	*cur_token;

	cur_list = g_var->token_list;
	while (cur_list != NULL)
	{
		cur_token = (t_token *) cur_list->content;
		switch (cur_token->type) {
			case T_NULL:
				printf("Token_type: T_NULL, ");
				break ;
			case T_WORD:
				printf("Token_type: T_WORD, ");
				break ;
			case T_PIPE:
				printf("Token_type: T_PIPE, ");
				break ;
			case T_REDIRECT:
				printf("Token_type: T_REDIRECT, ");
				break ;
			default:
				printf("Token_type: Unknown, ");
				break ;
		}
		printf("Token_value: %s\n", cur_token->value);
		cur_list = cur_list->next;
	}
	return (TRUE);
}
