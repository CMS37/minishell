#include "../../libs/libft/incs/libft.h"
#include "../../incs/parser.h"

t_bool	parsing(void);

t_bool	parsing(void)
{
	if (syntax_err_occurred())
		return (FALSE);
	create_cmd_list();
	return (TRUE);
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