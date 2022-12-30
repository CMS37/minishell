#ifndef EXECUTE_H
# define EXECUTE_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// execute.c
int		execute(void);

// execute_builtin.c
t_bool	is_builtin(t_list *token_list);
t_bool	execute_builtin(t_list *token_list);

// execute_extern.c
void	execute_extern(t_list *token_list);

// here_docs.c
t_bool	here_docs(void);

// redirections.c
t_bool	set_fd_in_redir(t_list *token_list);
int		open_file(const char *file, t_open_flag flag);

#endif