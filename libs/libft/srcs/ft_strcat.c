#include "../incs/libft.h"
#include <stdlib.h>

t_bool	ft_strcat(char *dest, const char *src)
{
	const size_t	dest_len = ft_strlen(dest) + ft_strlen(src) + 1;
	char *const		tmp = ft_calloc(dest_len, sizeof(char), "");

	ft_strlcpy(tmp, dest, ft_strlen(dest) + 1);
	ft_strlcat(tmp, src, ft_strlen(src) + 1);
	free(dest);
	dest = tmp;
	return (TRUE);
}