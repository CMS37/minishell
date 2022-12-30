#include "../incs/minishell.h"
#include "../libs/libft/incs/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
-할일(버그)목록 찾는중- (처리된거지우기)
input> echo 2 2 2 2  output > "2222" 로 나오는거 토큰확인필요! echo시 공백여부..(bash="2 2 2 2") 
		echo $? > 이거토큰도 환경변수로  echo "$?" > 0  echo '$?' > $? 이거두개는 토큰으로 잘넘어옴
input> "/bin/ls"  output> CMD_ERR 바로 절대경로오는경우도 실행여부
./minishell 입력하면 execute_extern함수에서 path가 (null)되서 커맨드에러 ->따로 처리함수작성?
env 환경변수중 SHLVL 깊이에따라 증가여부
export만 입력시 한줄마다 declart -x 붙어서 출력. 근데 정렬방식이 env하고 다른듯?..
input> cat 하고 입력상태에서 ctrl-\하면 Quit: 3  나오는거 이거 구현여부?...
*/

static t_bool	init_minishell(char **envp);
static t_bool	execute_cmd_line(const char *line);
void			exit_minishell(void);

// static t_bool	print_token_list(void);

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
		add_history(line);
		execute_cmd_line(line);
		free(line);
	}
	return (0);
}

static t_bool	init_minishell(char **envp)
{
	g_var = (t_var *) ft_calloc(sizeof(t_var), 1, "Failed to init var");
	init_termios();
	init_signal();
	init_env_list(envp);
	g_var->old_fd[0] = dup(STDIN_FILENO);
	g_var->old_fd[1] = dup(STDOUT_FILENO);
	return (TRUE);
}

static t_bool	execute_cmd_line(const char *line)
{
	if (lexer(line) == FALSE || !g_var->token_list)
		return (FALSE);

	// print_token_list();

	if (parsing())
		execute();

	dup2(g_var->old_fd[0], STDIN_FILENO);
	dup2(g_var->old_fd[1], STDOUT_FILENO);
	// printf("EXIT_STATUS: %d\n", g_var->exit_status); //test
	return (TRUE);
}

void	exit_minishell(void)
{
	printf("\033[1A");
	printf("\033[14C");
	printf(" exit\n");
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
