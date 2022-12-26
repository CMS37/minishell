#ifndef EXECUTE_H
# define EXECUTE_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// execute.c
int		execute(void);
char	*find_path(const char *cmd);

// execute_builtin.c
t_bool	is_builtin(t_list *token_list);
t_bool	execute_builtin(t_list *token_list);

// execute_extern.c
void	execute_extern(t_list *token_list);

// list_to_arr.c
char	**list_to_arr(t_list *token_list);

// here_docs.c
t_bool	here_docs(void);

// redirections.c
t_bool	set_fd_in_redir(t_list *token_list);
int		open_file(const char *file, t_open_flag flag);

#endif