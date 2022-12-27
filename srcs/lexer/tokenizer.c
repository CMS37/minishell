#include "../../incs/lexer.h"
#include <stdlib.h>

t_bool			tokenize(const char *line);
static t_list	*get_ifs(void);
static t_bool	is_ifs(int c);
static t_bool	is_meta(int c);
static t_bool	is_quote(int c);

t_bool	tokenize(const char *line)
{
	t_token	*cur;

	cur = init_token();
	while (*line)
	{
		if ((is_ifs(*line) || is_meta(*line)) && cur->value != NULL)
		{
			ft_lstadd_back(&g_var->token_list, ft_lstnew(cur));
			cur = init_token();
		}
		if (is_meta(*line))
			ft_lstadd_back(&g_var->token_list,
				ft_lstnew(init_meta_token(&line)));
		if (is_quote(*line))
			handle_quote(cur, &line);
		else if (!is_ifs(*line) && !is_meta(*line) && !is_quote(*line))
			cur->value = ft_strjoin(cur->value, ft_substr(line, 0, 1));
		line++;
	}
	if (cur->value != NULL)
		ft_lstadd_back(&g_var->token_list, ft_lstnew(cur));
	else
		free(cur);
	return (TRUE);
}

static t_list	*get_ifs(void)
{
	t_list	*ret;
	t_list	*tmp;
	char	*env;

	ret = NULL;
	ft_lstadd_back(&ret, ft_lstnew(ft_itoa(9)));
	ft_lstadd_back(&ret, ft_lstnew(ft_itoa(10)));
	ft_lstadd_back(&ret, ft_lstnew(ft_itoa(32)));
	tmp = g_var->env_list;
	while (tmp)
	{
		env = (char *) tmp->content;
		if (ft_strncmp(env, "IFS=", 4) == 0)
		{
			ft_lstclear(&ret, free);
			ret = NULL;
			env += 4;
			while (*env)
				ft_lstadd_back(&ret, ft_lstnew(ft_itoa(*env++)));
		}
		tmp = tmp->next;
	}
	return (ret);
}

static t_bool	is_ifs(int c)
{
	t_list	*ifs;
	t_list	*tmp;

	ifs = get_ifs();
	tmp = ifs;
	while (tmp)
	{
		if (c == ft_atoi((char *) tmp->content))
		{
			ft_lstclear(&ifs, free);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	ft_lstclear(&ifs, free);
	return (FALSE);
}

static t_bool	is_meta(int c)
{
	const char	meta[4] = {'|', '>', '<', '\0'};
	size_t		i;

	i = 0;
	while (meta[i])
	{
		if (c == meta[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static t_bool	is_quote(int c)
{
	return (c == '\'' || c == '\"');
}
