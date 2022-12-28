#ifndef BUINLTIN_H
# define BUINLTIN_H

# include "../libs/libft/incs/libft.h"
#include "subsystem.h"

// env.c
t_bool	init_env_list(char **envp);
int		builtin_env(t_list *token_list, int fd);

// export.c
int		builtin_export(t_list *token_list, int fd);

// pwd.c
int		builtin_pwd(t_list *token_list, int fd);

// unset.c
int		builtin_unset(t_list *token_list, int fd);

// exit.c
int		builtin_exit(t_list *token_list, int fd);
int		set_exit_status(int status);

#endif