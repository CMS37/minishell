#include "../../incs/parser.h"
#include "../../incs/structs.h"
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

void	parsing(t_list *list);

void	parsing(t_list *list)
{
	if (list == NULL)
		return ;
	check_unexpected_token(list);
	create_cmd_list();
	return ;
}
