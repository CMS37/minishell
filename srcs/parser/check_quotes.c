#include "../../incs/parser.h"

static void	del_node(t_list **list);
static void	remove_quote(t_list *list, int i);
static void	remove_quotes(int squte, int dqute);

int	check_quotes(t_list *tmp)
{
	t_token	*token;
	int		squte;
	int		dqute;

	squte = 0;
	dqute = 0;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		if (token->type == T_SINGLE_QUOTE)
		{
			if ((dqute % 2) != 1)
				squte++;
		}
		else if (token->type == T_DOUBLE_QUOTE)
		{
			if ((squte % 2) != 1)
				dqute++;
		}
		tmp = tmp->next;
	}
	if ((squte % 2) != 0 || (dqute % 2) != 0)
		return (FALSE);
	remove_quotes(squte, dqute);
	return (TRUE);
}

static void	remove_quotes(int squte, int dqute)
{
	t_list	*tmp;
	t_token	*token;

	tmp = g_var->token_list;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		if (token->type == T_SINGLE_QUOTE && squte > 0)
		{
			remove_quote(tmp, 1);
			squte -= 2;
		}
		else if (token->type == T_DOUBLE_QUOTE && dqute > 0)
		{
			remove_quote(tmp, 2);
			dqute -= 2;
		}
		tmp = tmp->next;
	}
}

static void	remove_quote(t_list *list, int i)
{
	t_list	*tmp;
	t_token	*token;
	t_token	*new_token;
	char	*str;
	int		cnt;

	str = ft_strdup("");
	cnt = 0;
	tmp = list;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if ((token->type == T_SINGLE_QUOTE && i == 1) || \
			(token->type == T_DOUBLE_QUOTE && i == 2))
		{
			cnt++;
			free(token->value);
			del_node(&tmp);
			if (cnt == 2)
				break ;
		}
		else if (token != NULL)
		{
			str = ft_strjoin(str, token->value);
			tmp = tmp->next;
		}
	}
	new_token = (t_token *) ft_calloc(sizeof(t_token), 1, "");
	new_token->value = str;
	printf("ARGV : %s\n", str);
	new_token->type = T_WORD;
	list->content = new_token;
	list->next = tmp;
}

static void	del_node(t_list **list)
{
	t_list	*tmp;

	free((*list)->content);
	tmp = (*list)->next;
	free ((*list));
	(*list) = tmp;
}
