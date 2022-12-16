#include "../includes/ft_printf.h"

int			ft_printf(const char *format, ...);
static int	ft_formats(va_list *args, const char format);

int	ft_printf(const char *str, ...)
{
	int		i;
	int		printed;
	va_list	args;

	i = 0;
	printed = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			printed += ft_formats(&args, str[++i]);
		else
			printed += ft_print_char(str[i]);
		i++;
	}
	va_end(args);
	return (printed);
}

static int	ft_formats(va_list *args, const char format)
{
	int	printed;

	printed = 0;
	if (format == 'c')
		printed += ft_print_char(va_arg(*args, int));
	else if (format == 's')
		printed += ft_print_str(va_arg(*args, char *));
	else if (format == 'p')
		printed += ft_print_ptr(va_arg(*args, unsigned long long));
	else if (format == 'd' || format == 'i')
		printed += ft_print_nbr(va_arg(*args, int));
	else if (format == 'u')
		printed += ft_print_unsigned_int(va_arg(*args, unsigned int));
	else if (format == 'x' || format == 'X')
		printed += ft_print_hex(va_arg(*args, unsigned int), format);
	else if (format == '%')
		printed += ft_print_char('%');
	return (printed);
}
