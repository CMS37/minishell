#include "../../incs/parser.h"
#include "../../incs/structs.h"
#include "../../incs/execute.h"


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