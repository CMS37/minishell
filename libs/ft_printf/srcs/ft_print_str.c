#include "../includes/ft_printf.h"

int	ft_print_str(const char *str)
{
	int	printed;

	printed = 0;
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (str[printed])
		printed += ft_print_char(str[printed]);
	return (printed);
}
