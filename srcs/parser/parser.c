#include "../../incs/parser.h"

void	parsing(void);
void	del_cmd(void *cmd);

void	parsing(void)
{
	// TODO: handle quotes
	if (check_syntax_err() == TRUE)
		return ;
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

/*
void	error(char	*str)
{
	// TODO: set exit_status: 258
	printf("minishell: syntax error near unexpected token `%s\'\n", str);
}

*/

