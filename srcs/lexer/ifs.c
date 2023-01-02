/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:42 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 14:58:30 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/lexer.h"
#include <stdlib.h>

t_bool			is_ifs(int c);
static t_list	*get_ifs(void);

t_bool	is_ifs(int c)
{
	t_list	*ifs;
	t_list	*tmp;

	ifs = get_ifs();
	tmp = ifs;
	while (tmp)
	{
		if (c == ft_atoi((char *) tmp->content))
		{
			ft_lstclear(&ifs, free);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	ft_lstclear(&ifs, free);
	return (FALSE);
}

static t_list	*get_ifs(void)
{
	t_list	*ret;
	t_list	*tmp;
	char	*env;

	ret = NULL;
	ft_lstadd_back(&ret, ft_lstnew(ft_itoa(9)));
	ft_lstadd_back(&ret, ft_lstnew(ft_itoa(10)));
	ft_lstadd_back(&ret, ft_lstnew(ft_itoa(32)));
	tmp = g_var->env_list;
	while (tmp)
	{
		env = (char *) tmp->content;
		if (ft_strncmp(env, "IFS=", 4) == 0)
		{
			ft_lstclear(&ret, free);
			ret = NULL;
			env += 4;
			while (*env)
				ft_lstadd_back(&ret, ft_lstnew(ft_itoa(*env++)));
		}
		tmp = tmp->next;
	}
	return (ret);
}
