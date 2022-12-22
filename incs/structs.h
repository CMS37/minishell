#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libs/libft/incs/libft.h"
# include <termios.h>

typedef struct termios	t_termios;

typedef enum e_token_type
{
	T_NULL = 0,
	T_WORD = 1,
	T_PIPE = 2,
	T_REDIRECT = 3,
	T_SINGLE_QUOTE = 4,
	T_DOUBLE_QUOTE = 5,
	T_ARGV = 6,
	T_CMD = 7
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef enum e_open_flag
{
	HERE_DOC = 0,
	FILE_IN = 1,
	FILE_OUT_TRUNC = 2,
	FILE_OUT_APPEND = 3,
}	t_open_flag;

typedef struct	s_var
{
	t_termios	old_term;
	t_termios	new_term;
	t_list		*token_list;
	t_list		*env_list;
	t_list		*cmd_list;
	size_t		here_doc_cnt;
	int			exit_status;
	int			old_fd[3];
}	t_var;

// (char **) cmd_list->value[0] == (char *) "ls"
// (char **) cmd_list->value[1] == (char *) "-a"
// (char **) cmd_list->value[2] == (char *) "-l"

// cmd_list = (cmd_list->next != NULL)
// (char **) cmd_list->value[0] == (char *) "wc"
// (char **) cmd_list->value[1] == (char *) "-l"

// cmd_list = (cmd_list->next != NULL)
// (char **) cmd_list->value[0] == (char *) "echo"
// (char **) cmd_list->value[1] == (char *) "a"
// (char **) cmd_list->value[2] == (char *) ">"
// (char **) cmd_list->value[3] == (char *) "b"

t_var	*g_var;

#endif