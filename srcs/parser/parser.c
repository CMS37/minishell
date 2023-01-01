#include "../../incs/parser.h"
#include "../../incs/utils.h"
#include "../../incs/structs.h"
#include <errno.h>
#include <string.h>

t_bool	parsing(void);

t_bool	parsing(void)
{
	if (syntax_err_occurred())
		return (FALSE);
	create_cmd_list();
	
	// 여기서 실행 하면 안되고 syntax_err_occurred 함수 안에서 실행 해야함
	if (here_docs() == FALSE)
	{
		if (g_var->exit_status == 258)
			return (print_err(258, NULL, NULL, SYNTAX_ERR) == 0);
		return (print_err(errno, NULL, NULL, strerror(errno)) == 0);
	}
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