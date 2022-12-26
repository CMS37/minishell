#include "../../incs/parser.h"

void		parsing(void);
void		syntax_error(void);
static void	del_cmd(void *cmd);

void	parsing(void)
{
	if (check_syntax_err())
		return ;
	ft_lstclear(&g_var->cmd_list, del_cmd);
	create_cmd_list();
	return ;
}

void	syntax_error(void)
{
	g_var->exit_status = 258;
	exit_status("syntax error", NULL, NULL);
}

static void	del_cmd(void *cmd)
{
	t_list	*t_cmd;

	t_cmd = (t_list *) cmd;
	ft_lstclear(&t_cmd, del_token);
}

/*

check_word.c

t_list *check_word_type(t_list *list)
{
	t_list	*tmp;
	t_token	*token;
	// int		i;
	
	tmp = list;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		if (token->type == T_WORD)
		{
			if (find_path(token->value) == NULL) // is not command
				;
		}
		tmp = tmp->next;
	}
	return (list);
}
*/