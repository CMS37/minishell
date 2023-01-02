/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:56:50 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 14:56:50 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// execute.c
int		execute(void);
t_bool	set_underscore_env(void);

// execute_builtin.c
t_bool	is_builtin(t_list *token_list);
t_bool	execute_builtin(t_list *token_list);

// execute_extern.c
void	execute_extern(t_list *token_list);

// redirections.c
t_bool	set_fd_in_redir(t_list *token_list);
int		open_file(const char *file, t_open_flag flag);

#endif