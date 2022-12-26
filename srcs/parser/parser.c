#include "../../incs/parser.h"

void	parsing(void);
void	del_cmd(void *cmd);
void	syntax_error(void);

void	parsing(void)
{
	// check_syntax_err();
	if (g_var->exit_status == 258)
		return ; // free필요할듯
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
