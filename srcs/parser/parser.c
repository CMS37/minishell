#include "../../incs/parser.h"
#include "../../incs/structs.h"
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

void	parsing(void);

void	parsing(void)
{
	check_unexpected_token();
	create_cmd_list();
	return ;
}
