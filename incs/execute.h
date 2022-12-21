#ifndef EXECUTE_H
# define EXECUTE_H

# include "../libs/libft/incs/libft.h"
# include "structs.h"

// execute.c
int		execute(void);

// here_docs.c
t_bool	here_docs(void);

// redirections.c
t_bool	set_file_descriptors(t_list *cmd_list);
int		open_file(const char *file, t_open_flag flag);

#endif