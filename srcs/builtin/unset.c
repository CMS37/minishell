#include "../../libs/libft/incs/libft.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/lexer.h"
#include <stdlib.h>

int	builtin_unset(t_list *token_list, int fd)
{
	const char	*key = ((t_token *) token_list->next->content)->value;
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
	(void) fd;
	return (set_exit_status(0) == 0);
}
