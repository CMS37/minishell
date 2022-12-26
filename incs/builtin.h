#ifndef BUINLTIN_H
# define BUINLTIN_H

# include "../libs/libft/incs/libft.h"

// env.c
t_bool	init_env_list(char **envp);
int		builtin_env(int fd);

// export.c
int		builtin_export(t_list *token_list);

// pwd.c
int		builtin_pwd(int fd);

// unset.c
int		builtin_unset(t_list *token_list);

#endif