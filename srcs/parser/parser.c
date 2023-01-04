/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:02 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 22:25:13 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"
#include "../../incs/utils.h"
#include "../../incs/structs.h"
#include <errno.h>
#include <string.h>

t_bool	parsing(void);

t_bool	parsing(void)
{
	if (g_var->token_list == NULL)
		return (FALSE);
	if (syntax_err_occurred())
	{
		if (g_var->exit_status == 258 << 8)
			return (print_err(258, NULL, NULL, SYNTAX_ERR) == 0);
		if (g_var->exit_status == 2)
		{
			ft_putendl_fd("", 1);
			return (FALSE);
		}
		return (print_err(errno, NULL, NULL, strerror(errno)) == 0);
	}
	create_cmd_list();
	return (TRUE);
}
