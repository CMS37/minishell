/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:56:46 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 23:18:29 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libs/libft/incs/libft.h"

// cd.c
int		builtin_cd(t_list *token_list, int fd);

// echo.c
int		builtin_echo(t_list *token_list, int fd);

// env.c
int		builtin_env(t_list *token_list, int fd);
t_list	*get_env(const char *key);
t_bool	init_env_list(int argc, char **argv, char **envp);

// exit.c
int		builtin_exit(t_list *token_list, int fd);
int		set_exit_status(int status);

// export.c
int		builtin_export(t_list *token_list, int fd);
t_bool	replace_value(t_list *env, const char *envp);

// pwd.c
int		builtin_pwd(t_list *token_list, int fd);
char	*ft_getcwd(void);
char	*get_oldpwd(void);

// unset.c
int		builtin_unset(t_list *token_list, int fd);

#endif