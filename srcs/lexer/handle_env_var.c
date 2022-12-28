#include "../../incs/lexer.h"
#include <stdlib.h>

t_bool			handle_env_var(t_token *token, const char **line);
static char		*get_key(const char **line);
static size_t	get_key_size(const char *line);
static char		*get_env(const char *key);

t_bool	handle_env_var(t_token *token, const char **line)
{
	char *const	key = get_key(line);

	if (key[0] == '?')
		ft_strcat(&token->value, ft_itoa(g_var->exit_status));
	else
		ft_strcat(&token->value, get_env(key));
	free(key);
	return (TRUE);
}

static char	*get_key(const char **line)
{
	const int	key_size = get_key_size(++(*line));
	char *const	ret = ft_calloc(key_size + 1, sizeof(char), "");

	ft_strlcpy(ret, *line, key_size + 1);
	*line += key_size - 1;
	return (ret);
}

static size_t	get_key_size(const char *line)
{
	size_t	ret;

	ret = 0;
	while (line[ret] && !is_ifs(line[ret]) &&
		line[ret] != '$' && line[ret] != '\"')
		ret++;
	return (ret);
}

static char		*get_env(const char *key)
{
	t_list	*tmp;
	size_t	key_len;

	tmp = g_var->env_list;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(key, tmp->content, key_len) == 0)
			return (tmp->content + key_len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}
