#include "../incs/minishell.h"
#include "../libs/libft/incs/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static t_bool	init_minishell(int argc, char **argv, char **envp);
static t_bool	init_var(void);
static t_bool	print_token_list(void);

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	init_minishell(argc, argv, envp);
	while (TRUE)
	{
		line = readline("minishell-1.0$ ");
		if (line == NULL && \
			printf("\033[1A") && printf("\033[14C") && printf(" exit\n"))
			exit(-1);
		if (g_var->token_list != NULL)
			ft_lstclear(&g_var->token_list, del_token);
		g_var->token_list = tokenize(line);
		print_token_list();
		parsing(g_var->token_list);
		add_history(line);
		if (ft_strncmp(line, "exit", 4) == 0 && ft_putstr_fd("exit\n", 1))
			break ;
		free(line);
	}
	free(line);
	return (0);
}

static t_bool	init_minishell(int argc, char **argv, char **envp)
{
	init_var();
	init_termios();
	init_signal();
	init_env_list(envp);

	(void) argc;
	(void) argv;
	(void) envp;
	return (TRUE);
}

static t_bool	init_var(void)
{
	g_var = (t_var *) ft_calloc(sizeof(t_var), 1, "Failed to init var");
	if (g_var == NULL)
		return (FALSE);
	return (TRUE);
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
			case T_SINGLE_QUOTE:
				printf("Token_type: T_SINGLE_QUOTE, ");
				break ;
			case T_DOUBLE_QUOTE:
				printf("Token_type: T_DOUBLE_QUOTE, ");
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
