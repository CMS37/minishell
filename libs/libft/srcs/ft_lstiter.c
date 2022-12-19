#include "../incs/libft.h"

void	ft_lstiter(t_list_libft *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
	return ;
}
