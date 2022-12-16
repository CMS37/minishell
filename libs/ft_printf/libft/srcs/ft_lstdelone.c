#include "../incs/libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list_libft *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
	return ;
}
