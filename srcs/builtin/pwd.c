/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:23 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/09 14:25:08 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/utils.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int	builtin_pwd(t_list *token_list, int fd)
{
	char	*pwd;

	pwd = ft_getcwd();
	if (pwd == NULL)
		return (print_err(errno, "pwd", NULL, "PWD not set"));
	ft_putendl_fd(pwd, fd);
	free(pwd);
	(void) token_list;
	return (g_var->exit_status);
}
