/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:03:47 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 15:04:08 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"
#include <stdlib.h>

t_bool	ft_strncat(char **dest, const char *src, size_t n)
{
	const size_t	dest_len = ft_strlen(*dest);
	const size_t	res_len = dest_len + n + 1;
	char *const		res = ft_calloc(sizeof(char), res_len, "");

	ft_strlcpy(res, *dest, dest_len + 1);
	ft_strlcat(res + dest_len, src, n + 1);
	if (*dest != NULL)
		free(*dest);
	*dest = res;
	return (TRUE);
}
