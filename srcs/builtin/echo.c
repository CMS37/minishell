#include "../../incs/builtin.h"

int			builtin_echo(t_list *token_list, int fd);
static int	check_arg(t_list *tmp);

int	builtin_echo(t_list *token_list, int fd)
{
	t_list	*tmp;
	int		n_flag;

	fd = 0;
	tmp = token_list;
	n_flag = 0;
	if (tmp->next != NULL)
		n_flag = (check_arg(tmp->next));
	if (n_flag)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	while (tmp)
	{
		ft_putstr_fd((char *)((t_token *)tmp->content)->value, 2);
		tmp = tmp->next;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 2);
	g_var->exit_status = 0;
	return (0);
}

static int	check_arg(t_list *tmp)
{
	t_token	*token;

	token = tmp->content;
	if (ft_strnstr(token->value, "-n", 2) != 0)
		return (1);
	return (0);
}
