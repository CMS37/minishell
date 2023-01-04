/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:02 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 19:12:23 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libs/libft/incs/libft.h"
# define IDENTIFIER_ERR "not a valid identifier"
# define NUMERIC_ERR "numeric argument required"
# define ARG_ERR "too many arguments"
# define CMD_ERR "command not found"
# define QUOTE_ERR "quote is not closed"
# define SYNTAX_ERR "syntax error"

// print_err.c
int		print_err(int status, char *cmd, char *arg, char *err_str);

// path.c
char	*home_dir(void);
char	*get_absolute_path(char *path);
char	*calc_relative_path(char *path);

// ft_getenv.c
char	**ft_getenv(void);

#endif