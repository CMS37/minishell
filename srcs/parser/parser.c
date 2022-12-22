#include "../../incs/parser.h"
#include "../../incs/structs.h"
#include "../../incs/lexer.h"
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

void	parsing(void);
void	del_cmd(void *cmd);

void	parsing(void)
{
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