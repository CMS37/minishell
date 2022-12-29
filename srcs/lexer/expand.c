#include "../../incs/lexer.h"
#include <stdlib.h>

t_bool			handle_expand(t_token *token, const char **line);
t_bool			is_expand(int c);
static char		*get_key(const char **line);
static size_t	get_key_size(const char *line);
static char		*get_value(const char *key);

t_bool	handle_expand(t_token *token, const char **line)
{
	char *const	key = get_key(line);

	if (key[0] == '?')
		ft_strcat(&token->value, ft_itoa(g_var->exit_status));
	else
		ft_strcat(&token->value, get_value(key));
	free(key);
	return (TRUE);
}

t_bool	is_expand(int c)
{
	return (c == '$');
}

static char	*get_key(const char **line)
{
	const int	key_size = get_key_size(*line + 1);
	char *const	ret = ft_calloc(sizeof(char), key_size + 1, "");

	ft_strlcpy(ret, *line + 1, key_size + 1);
	*line += key_size;
	return (ret);
}

static size_t	get_key_size(const char *line)
{
	size_t	ret;

	ret = 0;
	while (line[ret] && is_not_word(line[ret]) == FALSE)
		ret++;
	return (ret);
}

static char	*get_value(const char *key)
{
	t_list	*tmp;
	size_t	key_len;

	tmp = g_var->env_list;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(key, tmp->content, key_len) == 0 && \
			((char *)tmp->content)[key_len] == '=')
			return (tmp->content + key_len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}
