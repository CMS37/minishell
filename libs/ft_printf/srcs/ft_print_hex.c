#include "../includes/ft_printf.h"

int			ft_print_hex(unsigned int nbr, const char format);
static int	ft_put_hex(unsigned int nbr, const char format);

int	ft_print_hex(unsigned int nbr, const char format)
{
	if (!nbr)
		return (ft_print_char('0'));
	return (ft_put_hex(nbr, format));
}

static int	ft_put_hex(unsigned int nbr, const char format)
{
	int	printed;

	printed = 0;
	if (16 <= nbr)
	{
		printed += ft_put_hex(nbr / 16, format);
		printed += ft_put_hex(nbr % 16, format);
	}
	else
	{
		if (nbr < 10)
			printed += ft_print_char(nbr + '0');
		else
		{
			if (format == 'x')
				printed += ft_print_char('a' + (nbr - 10));
			else if (format == 'X')
				printed += ft_print_char('A' + (nbr - 10));
		}
	}
	return (printed);
}
