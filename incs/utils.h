#ifndef UTILS_H
# define UTILS_H

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
char	*convert_relative_path_to_absolute_path(const char *path);

// ft_getenv.c
char	**ft_getenv(void);

#endif