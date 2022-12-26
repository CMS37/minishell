#include "../../incs/parser.h"

void	parsing(void);
void	del_cmd(void *cmd);

void	parsing(void)
{
	check_syntax_err();
	if (g_var->exit_status != 0)
		return ;
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

void	syntax_error(void)
{
	g_var->exit_status = 258;
	exit_status("syntax error", NULL, NULL);
}