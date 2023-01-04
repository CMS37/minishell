/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:56:53 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 21:18:30 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// parser.c
t_bool	parsing(void);

// create_cmd_list.c
t_bool	create_cmd_list(void);
void	del_cmd(void *cmd);

// here_doc.c
t_bool	here_doc(char *file_name, char *end_flag);
char	*generate_file_name(void);

//syntax_err.c
t_bool	syntax_err_occurred(void);

#endif