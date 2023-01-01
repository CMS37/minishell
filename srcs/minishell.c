#include "../libs/libft/incs/libft.h"
#include "../incs/structs.h"
#include "../incs/subsystem.h"
#include "../incs/lexer.h"
#include "../incs/parser.h"
#include "../incs/execute.h"
#include "../incs/builtin.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
보류

export 정렬
변수와 환경변수의 차이를 이해하고 구현하기.
*/

/*
-할일(버그)목록 찾는중- (처리된거지우기)
1).	bash에서 ls>|cat 이딴게 실행됨. '>'랑 '|'가 붙어있을 때에만 이상 반응 보임
2).	here document를 parsing단계에서 토큰 하나하나 지날때 마다 오류있기 전까지 heredoc이 나타나면 바로 실행해야됨.
	오류가 있다면 해당 지점을 기준으로 뒤에 있는 heredoc은 실행하지 않음.
	ex) cat << EOF << EOF < a < b < << EOF (2번의 heredoc 실행)

syntax
leak check
pdf 다시 정독
minishell.png 다시 봐주시고
*/

static t_bool	init_minishell(int argc, char **argv, char **envp);
static t_bool	init_var(void);
static t_bool	execute_cmd_line(const char *line);
static void		exit_minishell(void);

// static t_bool	print_token_list(void);

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	
	init_minishell(argc, argv, envp);
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

	// print_token_list();

	if (parsing() == FALSE)
		return (FALSE);

	execute();

	dup2(g_var->old_fd[0], STDIN_FILENO);
	dup2(g_var->old_fd[1], STDOUT_FILENO);
	// printf("EXIT_STATUS: %d\n", g_var->exit_status); //test
	return (TRUE);
}

void	exit_minishell(void)
{
	ft_putstr_fd("\033[1A", 1);
	ft_putstr_fd("\033[14C", 1);
	ft_putstr_fd(" exit\n", 1);
	exit(0);
}

// static t_bool	print_token_list(void)
// {
// 	t_list	*cur_list;
// 	t_token	*cur_token;

// 	cur_list = g_var->token_list;
// 	while (cur_list != NULL)
// 	{
// 		cur_token = (t_token *) cur_list->content;
// 		switch (cur_token->type) {
// 			case T_NULL:
// 				printf("Token_type: T_NULL, ");
// 				break ;
// 			case T_WORD:
// 				printf("Token_type: T_WORD, ");
// 				break ;
// 			case T_PIPE:
// 				printf("Token_type: T_PIPE, ");
// 				break ;
// 			case T_REDIRECT:
// 				printf("Token_type: T_REDIRECT, ");
// 				break ;
// 			default:
// 				printf("Token_type: Unknown, ");
// 				break ;
// 		}
// 		printf("Token_value: %s\n", cur_token->value);
// 		cur_list = cur_list->next;
// 	}
// 	return (TRUE);
// }
