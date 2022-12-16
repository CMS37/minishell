#include "../incs/libft.h"
#include <stdlib.h>

t_list_libft	*ft_lstnew(void *content)
{
	t_list_libft	*new;

	new = (t_list_libft *) malloc(sizeof(t_list_libft));
	if (!new)
		return (0);
	new->content = content;
	new->next = 0;
	return (new);
}
