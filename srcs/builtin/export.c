#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <stdlib.h>

int		builtin_export(t_list *token_list);
t_list	*get_env(const char *key);
t_bool	replace_value(t_list *env, const char *envp);
t_bool	key_is_not_valid(const char *key);

int	builtin_export(t_list *token_list)
{
	t_list	*env;
	t_token	*token;
	char	*key;

	if (ft_lstsize(token_list) == 1)
		builtin_env(STDOUT_FILENO);
	else
	{
		token = token_list->next->content;
		key = ft_substr(token->value, 0,
				ft_strchr(token->value, '=') - token->value);
		if (key_is_not_valid(key))
			return (1);
		env = get_env(key);
		if (env == NULL)
			ft_lstadd_back(&g_var->env_list, ft_lstnew(token->value));
		else
			replace_value(env, token->value);
	}
	return (0);
}

t_list	*get_env(const char *key)
{
	t_list	*ret;
	char	*envp;

	ret = g_var->env_list;
	while (ret)
	{
		envp = ret->content;
		if (ft_strncmp(envp, key, ft_strlen(key)) == 0)
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
	ft_putendl_fd(key, 2);
	if (*key == 0)
		return (TRUE);
	if (ft_isalpha(*key) == 0 && *key != '_')
		return (TRUE);
	while (*key)
	{
		if (ft_isalnum(*key) == 0 && *key != '_')
			return (TRUE);
		key++;
	}
	return (FALSE);
}

/*
export수정하실때 exit코드 참고하시라구...
exit_status("export", key?, IDENTIFIER_ERR);
(export 첫 인자와 =을 띄어 쓴 경우 || export나 unset 인자에 숫자가 포함된 경우) = IDENTIFIER_ERR
*/