#include "../incs/libft.h"
#include <stdlib.h>

void			*ft_calloc(size_t sz_, size_t count, const char *error_msg);
static t_bool	is_invalid_input(size_t sz_, size_t count);

void		*ft_calloc(size_t sz_, size_t count, const char *error_msg)
{
	void	*res;

	if (is_invalid_input(count, sz_))
		ft_exit_with_error(error_msg, 1);
	res = malloc(sz_ * count);
	if (!res)
		ft_exit_with_error(error_msg, 1);
	ft_bzero(res, (sz_ * count));
	return (res);
}

static t_bool	is_invalid_input(size_t sz_, size_t count)
{
	if (SIZE_MAX <= sz_ || SIZE_MAX <= count)
		return (TRUE);
	if (sz_ && SIZE_MAX / sz_ <= count)
		return (TRUE);
	return (FALSE);
}
