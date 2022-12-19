#include "../incs/libft.h"

int	ft_lstsize(t_list_libft *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
