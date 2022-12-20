#include "../../incs/lexer.h"
#include <stdlib.h>

t_list			*tokenize(const char *line);
static t_list	*get_ifs(void);
static t_bool	is_ifs(int c);
static t_bool	is_meta(int c);

t_list	*tokenize(const char *line)
{
	t_list	*ret;
	t_token	*cur_token;
	size_t	i;

	ret = NULL;
	cur_token = NULL;
	i = 0;
	while (i < ft_strlen(line))
	{
		if ((is_ifs(line[i]) || is_meta(line[i])) && cur_token != NULL)
		{
			ft_lstadd_back(&ret, ft_lstnew(cur_token));
			cur_token = NULL;
		}
		if (is_meta(line[i]))
			ft_lstadd_back(&ret, ft_lstnew(init_meta_token(line, &i)));
		if (is_ifs(line[i]) == FALSE && is_meta(line[i]) == FALSE)
		{
			if (cur_token == NULL)
				cur_token = init_token();
			cur_token->value = ft_strjoin(cur_token->value, ft_substr(line, i, 1));
		}
		i++;
	}
	if (cur_token != NULL)
		ft_lstadd_back(&ret, ft_lstnew(cur_token));
	return (ret);
}

static t_list	*get_ifs(void)
{
	t_list	*ret;
	t_list	*tmp;
	char	*env;

	ret = NULL;
	ft_lstadd_back(&ret, ft_lstnew(ft_strdup(ft_itoa(9))));
	ft_lstadd_back(&ret, ft_lstnew(ft_strdup(ft_itoa(10))));
	ft_lstadd_back(&ret, ft_lstnew(ft_strdup(ft_itoa(32))));
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
				ft_lstadd_back(&ret, ft_lstnew(ft_strdup(ft_itoa(*env++))));
		}
		tmp = tmp->next;
	}
	return (ret);
}

static t_bool	is_ifs(int c)
{
	t_list *const	ifs = get_ifs();
	t_list			*tmp;

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
	const char	*meta = "><$|\'\"";
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
