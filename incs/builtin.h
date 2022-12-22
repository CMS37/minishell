#ifndef BUINLTIN_H
# define BUINLTIN_H

# include "../libs/libft/incs/libft.h"

// env.c
t_bool	init_env_list(char **envp);
int		builtin_env(int fd);

// export.c
t_bool	builtin_export(t_list *cmd);

// pwd.c
int		builtin_pwd(int fd);

#endif