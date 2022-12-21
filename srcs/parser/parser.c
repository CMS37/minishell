#include "../../incs/parser.h"
#include "../../incs/structs.h"

/*
처리한문법
  1.파이프만 있거나 다음입력값이 인자가아닐경우
	-> ("|", "| <", "| ||", "| pwd")등
  2.리다이렉션다음에 입력값이있을떄 
  	인자가아닌 명렁어나 파이프가오면 에러
	-> ("< |", "pwd > a", )근데 이건되나...? 배쉬테스트필요
  3. 그 외 처리할거?

	아직 코드 최적화 및 디버깅x 테스트필

	할거
	디버깅/최적화/ 토큰타입에 값안들어가는거 확인
*/

void	check_syntax_err(t_list *list)
{
	t_list	*tmp;
	t_token	*token;
	t_token	*prev;
	t_token *next;

	tmp = list;
	prev = NULL;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		tmp = tmp->next;
		next = (t_token *) tmp->content;
		if (token->type == T_PIPE && (prev == NULL || \
			next == NULL || prev->type != T_ARGV || \
			next->type == T_PIPE))
			token->type = 1;
		if (token->type >= T_RED_R && token->type <= T_RED_LL && \
			(next != NULL && next->type != T_ARGV))
			token->type = 1;
		prev = token;
	}
}

void	error(char	*str)
{
	//$? = 258
	printf("minishell: syntax error near unexpected token `%s\'\n", str);
}

void check_unexpected_token(t_list *list)
{
	t_list	*tmp;
	t_token	*token;

void	parsing(t_list *list);

void	parsing(void)
{
	if (list == NULL)
		return ;
	check_unexpected_token(list);
	create_cmd_list();
	return ;
}

/*
char	**find_cmd(t_list *list)
{
	t_list	*tmp;
	t_token	*token;
	char	**cmd;
	int		i;
	
	i = next_pipe(list);
	tmp = list;
	cmd = (char **) malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		cmd[i] = ft_strdup(token->value);
		if (cmd[i] == NULL)
		{
			free_cmd(cmd);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	cmd[i] = "\0";
	return (cmd);
}

void	set_cmd(t_list *list)
{
	int		i;
	t_list	*tmp;

	i = all_pipe(list);
	tmp = (t_list *) malloc(sizeof(t_list) * (i + 1));
	if (!tmp)
		return ;
	g_var->cmd_list = tmp;
	while(i--)
	{
		tmp->content = find_cmd(list);
		if (tmp->content == NULL)
			break ;
		char	*cur = tmp->content; //test
		printf("%s", cur);
		tmp = tmp->next;
	}
}*/