/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:51 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 14:58:30 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/lexer.h"
#include <stdlib.h>

t_token	*init_token(void);
t_token	*clone_token(t_token *token);
void	del_token(void *content);

t_token	*init_token(void)
{
	t_token	*ret;

	ret = ft_calloc(sizeof(t_token), 1, "Fail to init token");
	ret->type = T_WORD;
	ret->value = ft_strdup("");
	return (ret);
}

t_token	*clone_token(t_token *token)
{
	t_token *const	ret = ft_calloc(sizeof(t_token), 1, "");

	ret->type = token->type;
	ret->value = ft_strdup(token->value);
	return (ret);
}

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *) content;
	free(token->value);
	free(token);
	return ;
}
