#include "../../libs/libft/incs/libft.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int		builtin_export(t_list *token_list, int fd);
t_list	*get_env(const char *key);
t_bool	replace_value(t_list *env, const char *envp);
t_bool	key_is_not_valid(const char *key);

int	builtin_export(t_list *token_list, int fd)
{
	t_list	*env;
	t_token	*token;

	if (ft_lstsize(token_list) == 1)
		builtin_env(token_list, fd);
	else
	{
		token = token_list->next->content;
		if (key_is_not_valid(token->value) == FALSE)
		{
			env = get_env(token->value);
			if (env == NULL)
				ft_lstadd_back(&g_var->env_list,
					ft_lstnew(ft_strdup(token->value)));
			else
				replace_value(env, token->value);
		}
	}
	return (set_exit_status(0) == 0);
}

t_list	*get_env(const char *key)
{
	t_list	*ret;
	char	*envp;

	ret = g_var->env_list;
	while (ret)
	{
		envp = ret->content;
		if (ft_strncmp(envp, key, ft_strchr(key, '=') - key) == 0)
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

t_bool	replace_value(t_list *env, const char *envp)
{
	free(env->content);
	env->content = ft_strdup(envp);
	return (TRUE);
}

t_bool	key_is_not_valid(const char *key)
{
	if (*key == 0)
		return (print_err(EINVAL, "export", NULL, strerror(EINVAL)));
	if (ft_isalpha(*key) == 0 && *key != '_')
		return (print_err(EINVAL, "export", NULL, strerror(EINVAL)));
	while (*key)
	{
		if (*key == '=')
			break ;
		if (ft_isalnum(*key) == 0 && *key != '_')
			return (print_err(EINVAL, "export", NULL, strerror(EINVAL)));
		key++;
	}
	return (FALSE);
}

/*
export수정하실때 exit코드 참고하시라구...
exit_status("export", key?, IDENTIFIER_ERR);
(export 첫 인자와 =을 띄어 쓴 경우 || export나 unset 인자에 숫자가 포함된 경우) = IDENTIFIER_ERR
*/