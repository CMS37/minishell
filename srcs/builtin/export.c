#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <stdlib.h>

int		builtin_export(t_list *token_list);
t_list	*get_env(const char *key);
t_bool	replace_value(t_list *envp, const char *value);

int		builtin_export(t_list *token_list)
{
	t_list	*env;
	t_token	*token;
	char	*key;
	char	*value;

	if (ft_lstsize(token_list) == 1)
		builtin_env(STDOUT_FILENO);
	else
	{
		token = token_list->next->content;
		key = NULL;
		value = ft_strchr(token->value, '=');
		if (token->type == T_WORD && token->value != value)
		{
			key = ft_substr(token->value, 0, value - token->value + 1);
			value = ft_strdup(value + 1);
			env = get_env(key);
			if (env == NULL)
				ft_lstadd_back(&g_var->env_list, ft_lstnew(ft_strjoin(key, value)));
			else
				replace_value(env, value);
		}
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

t_bool	replace_value(t_list *envp, const char *value)
{
	char	*env;
	char	*key;

	env = envp->content;
	key = ft_substr(env, 0, ft_strchr(env, '=') - env + 1);
	env = ft_strjoin(key, value);
	free(envp->content);
	envp->content = env;
	return (TRUE);
}
