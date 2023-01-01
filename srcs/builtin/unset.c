#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/utils.h"
#include <stdlib.h>

int				builtin_unset(t_list *token_list, int fd);
static t_bool	unset_env(t_list *token_list);

int	builtin_unset(t_list *token_list, int fd)
{
	t_token	*token;

	token_list = token_list->next;
	while (token_list)
	{
		token = token_list->content;
		if (unset_env(token_list) == FALSE)
			return (print_err(1, "unset", token->value, IDENTIFIER_ERR));
		token_list = token_list->next;
	}
	(void) fd;
	return (g_var->exit_status);
}

static t_bool	unset_env(t_list *token_list)
{
	const char	*key = ((t_token *) token_list->content)->value;
	t_list		*prev;
	t_list		*cur;

	prev = NULL;
	cur = g_var->env_list;
	while (cur)
	{
		if (ft_strncmp(cur->content, key, ft_strlen(key)) == 0)
		{
			if (prev == NULL)
				g_var->env_list = cur->next;
			else
				prev->next = cur->next;
			ft_lstdelone(cur, free);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (TRUE);
}
