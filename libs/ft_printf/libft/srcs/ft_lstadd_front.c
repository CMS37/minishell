#include "../incs/libft.h"

void	ft_lstadd_front(t_list_libft **lst, t_list_libft *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
	return ;
}
