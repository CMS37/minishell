#include "../../libs/libft/incs/libft.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/subsystem.h"
#include <unistd.h>
#include <limits.h>

int				builtin_exit(t_list *token_list, int fd);
int				set_exit_status(int status);
static t_bool	is_num(const char *str);

int	builtin_exit(t_list *token_list, int fd)
{
	t_list		*tmp;
	t_token		*token;
	long long	i;

	tmp = token_list->next;
	ft_putendl_fd("exit", fd);
	if (tmp == NULL)
		exit(set_exit_status(0));
	token = tmp->content;
	if (is_num(token->value) == FALSE)
		exit(print_err(255, "exit", token->value, NUMERIC_ERR));
	if (tmp->next != NULL)
		return (print_err(1, "exit", NULL, ARG_ERR));
	i = ft_atoll(token->value);
	if (i < INT_MIN || INT_MAX < i)
		exit(print_err(255, "exit", token->value, NUMERIC_ERR));
	if (i < 0)
		i = (256 - ((i * -1) % 256));
	i = (i % 256);
	exit(set_exit_status(i));	
	return (1);
}

int	set_exit_status(int status)
{
	g_var->exit_status = status;
	return (status);
}

static t_bool	is_num(const char *str)
{
	while (str && *str)
	{
		if (('0' <= *str && *str <= '9') == FALSE)
			return (FALSE);
		str++;
	}
	return (TRUE);
}
