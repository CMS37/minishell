#include "../incs/libft.h"

t_list_libft	*ft_lstlast(t_list_libft *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
