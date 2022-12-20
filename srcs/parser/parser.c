#include "../../incs/parser.h"
#include "../../incs/structs.h"

/*
lexer 에서 들어온 문자열 토큰화 후 전달 -> 구조체로 리턴받을듯?

구조체 받아서 오류 검사 후 파싱트리?

rule 1. 맨처음 토큰에 해당문자는 올수없음 {"|", "||", ...};
*/

#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

void	error(char	*str)
{
	//$? = 258
	printf("minishell: syntax error near unexpected token `%s\'\n", str);
}

void check_unexpected_token(t_list *list)
{
	t_list	*tmp;
	t_token	*token;

	tmp = list;
	token = (t_token *) tmp->content;
	if (token == NULL)
		return ;
	if (is_unexpected_token(token->value))
		error(token->value);
	while (tmp && (ft_strcmp(token->value, "<") == 0 || ft_strcmp(token->value, ">") == 0))
	{
		tmp = tmp->next;
		token = (t_token *)tmp->content;
		if (is_unexpected_token(token->value))
			error(token->value);
	}
	return ;
}

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
			// TODO: free cmds
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
		//test
		printf("%s", tmp->content);
		if (tmp->content == NULL)
			break ;
		tmp = tmp->next;
	}
}

void	parsing(t_list *list)
{
	if (list == NULL)
		return ;
	check_unexpected_token(list);
	// set_cmd(list);
	return ;
}

/*
int	main(void)
{
	t_list	*head;
	t_list	*list;
	t_token	*token;
	
	parsing()

	return (1);
}
*/