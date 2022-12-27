#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/subsystem.h"
#include <unistd.h>
#include <limits.h>

int			builtin_exit(t_list *token_list, int fd);
int			builtin_exit_status(t_list *token_list, int fd);
static int	exit_err(void);
static int	exit_err2(char *str);

int	builtin_exit(t_list *token_list, int fd)
{
	t_list		*tmp;
	t_token		*token;
	long long	i;

	tmp = token_list;
	i = 0;
	ft_putendl_fd("exit", fd);
	if (tmp->next != NULL)
	{
		tmp = tmp->next;
		token = (t_token *) tmp->content;
		if (tmp->next != NULL)
			return (exit_err());
		i = ft_atoi(token->value); // ft_atoi에서 범위값 long long 으로 수정필요 ->libft..수정해도될까유
		if (i > LLONG_MAX || i < LLONG_MIN)
			return (exit_err2(token->value));
		else if (i < 0)
			i = (256 - ((i * -1) % 256));
		else
			i = (i % 256);
	}
	g_var->exit_status = i;
	exit(i); //훔...ft_putendl_fd로 실행되는거같은데 일단 모르는거니 보류
	return (0);
}

int	builtin_exit_status(t_list *token_list, int fd)
{
	char	*err_num;

	err_num = ft_itoa(g_var->exit_status);
	g_var->exit_status = 127;
	exit_status(err_num, CMD_ERR, NULL);
	(void) token_list;
	(void) fd;
	return (1);
}

static int	exit_err(void)
{
	g_var->exit_status = 1;
	exit_status("exit", ARG_ERR, NULL);
	return (1);
}

static int	exit_err2(char *str)
{
	g_var->exit_status = 255;
	exit_status("exit", str, NUMERIC_ERR);
	return (1);
}
