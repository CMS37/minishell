#include "../incs/libft.h"

void	ft_lstclear(t_list_libft **lst, void (*del)(void *))
{
	t_list_libft	*tmp;
	t_list_libft	*to_del;

	tmp = *lst;
	while (tmp)
	{
		to_del = tmp;
		tmp = tmp->next;
		ft_lstdelone(to_del, del);
	}
	*lst = 0;
	return ;
}
