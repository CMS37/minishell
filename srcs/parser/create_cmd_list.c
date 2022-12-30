#include "../../libs/libft/incs/libft.h"
#include "../../incs/parser.h"
#include "../../incs/structs.h"
#include "../../incs/lexer.h"

t_bool	create_cmd_list(void);

t_bool	create_cmd_list(void)
{
	t_list	*cmd;
	t_list	*tmp;

	cmd = NULL;
	tmp = g_var->token_list;
	while (tmp)
	{
		if (((t_token *) tmp->content)->type == T_PIPE)
		{
			ft_lstadd_back(&g_var->cmd_list, ft_lstnew(cmd));
			cmd = NULL;
		}
		else
			ft_lstadd_back(&cmd, ft_lstnew(clone_token(tmp->content)));
		tmp = tmp->next;
	}
	if (cmd != NULL)
		ft_lstadd_back(&g_var->cmd_list, ft_lstnew(cmd));
	return (TRUE);
}
