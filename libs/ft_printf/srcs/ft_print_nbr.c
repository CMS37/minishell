#include "../includes/ft_printf.h"
#include <stdlib.h>

int	ft_print_nbr(const int nbr)
{
	char	*num;
	int		printed;

	num = ft_itoa(nbr);
	if (!num)
		return (0);
	printed = ft_print_str(num);
	free(num);
	return (printed);
}
