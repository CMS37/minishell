#include "../../incs/lexer.h"
#include <stdlib.h>

t_list			*tokenize(const char *line);
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

static t_bool	is_ifs(int c)
{
	return ((9 <= c && c <= 13) || c == 32);
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
