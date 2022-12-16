#include "../includes/ft_printf.h"
#include <stdlib.h>

int			ft_print_ptr(unsigned long long ptr);
static int	ft_put_ptr(uintptr_t num);

int	ft_print_ptr(unsigned long long ptr)
{
	int	printed;

	printed = ft_print_str("0x");
	if (!ptr)
		printed += ft_print_char('0');
	else
		printed += ft_put_ptr(ptr);
	return (printed);
}

static int	ft_put_ptr(uintptr_t num)
{
	int	printed;

	printed = 0;
	if (16 <= num)
	{
		printed += ft_put_ptr(num / 16);
		printed += ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			printed += ft_print_char(num + '0');
		else
			printed += ft_print_char('a' + (num - 10));
	}
	return (printed);
}
