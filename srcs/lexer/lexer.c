/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:44 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/05 23:59:50 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/lexer.h"
#include "../../incs/utils.h"
#include <errno.h>

t_bool	lexer(char **line)
{
	if (**line == '\0')
		return (FALSE);
	if (tokenize(*line) == FALSE)
		return (print_err(EINVAL, *line, NULL, QUOTE_ERR) == 0);
	return (TRUE);
}
