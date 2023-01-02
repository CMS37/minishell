/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:22 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 14:58:30 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"
#include "../../incs/structs.h"

char	**ft_getenv(void)
{
	const size_t	sz = ft_lstsize(g_var->env_list);
	char **const	ret = ft_calloc(sizeof(char *), sz + 1, "");
	t_list			*tmp;
	size_t			i;

	tmp = g_var->env_list;
	i = 0;
	while (tmp)
	{
		ret[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	return (ret);
}
