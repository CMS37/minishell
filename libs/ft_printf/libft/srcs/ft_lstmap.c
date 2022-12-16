#include "../incs/libft.h"

t_list_libft	*ft_lstmap(t_list_libft *lst, \
							void *(*f)(void *), void (*del)(void *))
{
	t_list_libft	*res;
	t_list_libft	*tmp;

	if (!lst || !f)
		return (0);
	res = 0;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&res, del);
			return (0);
		}
		ft_lstadd_back(&res, tmp);
		tmp = tmp->next;
		lst = lst->next;
	}
	return (res);
}
