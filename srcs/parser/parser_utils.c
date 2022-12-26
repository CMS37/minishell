#include "../../incs/parser.h"

void	syntax_error(void)
{
	g_var->exit_status = 258;
	printf("minishell: syntax error\n");
}
