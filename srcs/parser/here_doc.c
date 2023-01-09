/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:00 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/09 14:34:24 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"
#include "../../incs/execute.h"
#include "../../incs/lexer.h"
#include "../../incs/builtin.h"
#include "../../incs/subsystem.h"
#include "../../incs/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>

t_bool			here_doc(char *file_name, char *end_flag);
char			*generate_file_name(void);
static char		*tmp_directory_path(void);
static char		*generate_random_hexcode(void);
static t_bool	convert_expand(char **line);

t_bool	here_doc(char *file_name, char *end_flag)
{
	const int	fd = open_file(file_name, HERE_DOC);
	char		*line;

	if (fd == -1)
	{
		free(file_name);
		return (set_exit_status(errno) == 0);
	}
	while (TRUE)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, end_flag) == 0)
			break ;
		convert_expand(&line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	close(fd);
	return (TRUE);
}

char	*generate_file_name(void)
{
	char	*ret;
	char	*hex_code;

	ret = tmp_directory_path();
	hex_code = generate_random_hexcode();
	ft_strcat(&ret, ".heredoc_tmp_0x");
	ft_strcat(&ret, hex_code);
	free(hex_code);
	return (ret);
}

static char	*tmp_directory_path(void)
{
	t_list	*tmp;

	tmp = g_var->env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "TMPDIR=", 7) == 0)
			return (ft_strdup(tmp->content + 7));
		tmp = tmp->next;
	}
	return (ft_strdup("/"));
}

static char	*generate_random_hexcode(void)
{
	const char	*hex = "0123456789abcdef";
	char *const	ret = ft_calloc(sizeof(char), 9, "");
	const int	fd = open("/dev/urandom", O_RDONLY);
	size_t		i;

	if (fd == -1)
		return (ret);
	read(fd, ret, 8);
	close(fd);
	i = 0;
	while (i < 8)
	{
		if (ret[i] < 0)
			ret[i] *= -1;
		ret[i] = hex[ret[i] % 16];
		i++;
	}
	return (ret);
}

static t_bool	convert_expand(char **line)
{
	const char	*exp = ft_strchr(*line, '$');
	char		*res;
	char		*exp_tmp;

	if (exp == NULL)
		return (TRUE);
	res = ft_substr(*line, 0, exp - *line);
	exp_tmp = expand((char **) &exp);
	ft_strcat(&res, exp_tmp);
	free(exp_tmp);
	ft_strcat(&res, exp + 1);
	free(*line);
	*line = res;
	return (TRUE);
}
