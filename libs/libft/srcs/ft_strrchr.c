/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:03:57 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 15:04:08 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	target;
	char	*res;

	target = (char) c;
	res = 0;
	while (*s)
	{
		if (*s == target)
			res = (char *) s;
		s++;
	}
	if (*s == target)
		res = (char *) s;
	if (res)
		return (res);
	return (0);
}
