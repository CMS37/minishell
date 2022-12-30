#include "../../libs/libft/incs/libft.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/utils.h"
#include "../../incs/lexer.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int				builtin_export(t_list *token_list, int fd);
t_list			*get_env(const char *key);
t_bool			replace_value(t_list *env, const char *envp);
static t_bool	key_is_not_valid(const char *key);
static int		printenv(int fd);

int	builtin_export(t_list *token_list, int fd)
{
	t_list	*env;
	t_token	*token;
	t_list	*last_executed;

	if (ft_lstsize(token_list) == 1)
		return (printenv(fd));
	token_list = token_list->next;
	while (token_list)
	{
		last_executed = ft_lstlast(g_var->env_list);
		token = token_list->content;
		if (key_is_not_valid(token->value))
			return (print_err(1, "export", token->value, IDENTIFIER_ERR));
		env = get_env(token->value);
		if (env == NULL)
		{
			ft_lstadd_back(&g_var->env_list, ft_lstnew(ft_strdup(token->value)));
			ft_swap(&last_executed->content, &last_executed->next->content);
		}
		else
			replace_value(env, token->value);
		token_list = token_list->next;
	}
	return (g_var->exit_status);
}

t_list	*get_env(const char *key)
{
	t_list	*ret;
	size_t	key_len;

	ret = g_var->env_list;
	key_len = ft_strlen(key);
	if (ft_strchr(key, '=') != NULL)
		key_len = ft_strchr(key, '=') - key;
	while (ret)
	{
		if (ft_strncmp(ret->content, key, key_len) == 0)
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

t_bool	replace_value(t_list *env, const char *envp)
{
	if (ft_strchr(envp, '=') == NULL)
		return (TRUE);
	if (env->content != NULL)
		free(env->content);
	env->content = ft_strdup(envp);
	return (TRUE);
}

static t_bool	key_is_not_valid(const char *key)
{
	if (*key == 0)
		return (TRUE);
	if (ft_isalpha(*key) == 0 && *key != '_')
		return (TRUE);
	while (*key)
	{
		if (*key == '=')
			break ;
		if (ft_isalnum(*key) == 0 && *key != '_')
			return (TRUE);
		key++;
	}
	return (FALSE);
}

static int	printenv(int fd)
{
	t_list	*env;
	char	*c;

	env = g_var->env_list;
	while (env->next)
	{
		ft_putstr_fd("declare -x ", fd);
		c = env->content;
		while (*c && *c != '=')
			ft_putchar_fd(*c++, fd);
		if (*c == '=')
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(c + 1, fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
		env = env->next;
	}
	return (g_var->exit_status);
}
