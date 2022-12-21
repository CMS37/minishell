#include "../../incs/parser.h"
#include "../../incs/structs.h"
#include <stdio.h>
#include <stdlib.h>

void			check_unexpected_token(void);
static t_bool	is_unexpected_token(const char *token);
static void		print_unexpected_token_error(char *str);

void	check_unexpected_token(void)
{
	t_list	*tmp;
	t_token	*token;

	tmp = g_var->token_list;
	if (tmp == NULL)
		return ;
	token = (t_token *) tmp->content;
	if (token == NULL)
		return ;
	if (is_unexpected_token(token->value))
		print_unexpected_token_error(token->value);
	while (tmp && (ft_strcmp(token->value, "<") == 0 || ft_strcmp(token->value, ">") == 0))
	{
		tmp = tmp->next;
		token = (t_token *)tmp->content;
		if (is_unexpected_token(token->value))
			print_unexpected_token_error(token->value);
	}
	return ;
}

static t_bool	is_unexpected_token(const char *token)
{
	if (!ft_strcmp(token, "|"))
		return (TRUE);
	if (!ft_strcmp(token, ">") || !ft_strcmp(token, "<"))
		return (TRUE);
	if (!ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
		return (TRUE);
	if (!ft_strcmp(token, "'") || !ft_strcmp(token, "\""))
		return (TRUE);
	return (FALSE);
}

void	print_unexpected_token_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s\'\n", str);
	exit(258);
}
