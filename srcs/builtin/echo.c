#include "../../incs/builtin.h"

int	builtin_echo(t_list *token_list, int fd);

int	builtin_echo(t_list *token_list, int fd)
{
	t_token *token;
	t_bool	n_flag;

	token_list = token_list->next;
	token = token_list->content;
	n_flag = (ft_strnstr(token->value, "-n", 2) != NULL);
	if (n_flag == TRUE)
		token_list = token_list->next;
	while (token_list)
	{
		token = token_list->content;
		ft_putstr_fd(token->value, fd);
		token_list = token_list->next;
	}
	if (n_flag == FALSE)
		ft_putstr_fd("\n", fd);
	return (g_var->exit_status);
}
