#include "../../incs/parser.h"
#include "../../incs/lexer.h"
#include "../../incs/structs.h"
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

void	parsing(void);
void	del_cmd(void *cmd);

void	parsing(void)
{
	// TODO: handle quotes
	check_unexpected_token();
	ft_lstclear(&g_var->cmd_list, del_cmd);
	create_cmd_list();
	return ;
}

void	del_cmd(void *cmd)
{
	t_list	*t_cmd;

	t_cmd = (t_list *) cmd;
	ft_lstclear(&t_cmd, del_token);
}

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
		if (token->type >= T_REDIRECT && \
			(next != NULL && next->type != T_ARGV))
			token->type = 1;
		prev = token;
	}
}

// void	error(char	*str)
// {
//	// TODO: set exit_status: 258
// 	printf("minishell: syntax error near unexpected token `%s\'\n", str);
// }
