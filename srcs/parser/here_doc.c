/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:58:00 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/02 15:14:27 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"
#include "../../incs/execute.h"
#include "../../incs/lexer.h"
#include "../../incs/builtin.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <readline/readline.h>

t_bool			here_doc(t_token *token);
static char		*generate_file_name(void);
static char		*tmp_directory_path(void);
static t_bool	convert_expand(char **line);

t_bool	here_doc(t_token *token)
{
	char *const	file_name = generate_file_name();
	const int	fd = open_file(file_name, HERE_DOC);
	char		*line;

	if (fd == -1)
		return (set_exit_status(errno) == 0);
	while (TRUE)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, (token->value)) == 0)
			break ;
		convert_expand(&line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	free(token->value);
	token->value = file_name;
	close(fd);
	return (TRUE);
}

static char	*generate_file_name(void)
{
	char	*ret;

	++g_var->here_doc_cnt;
	ret = ft_strjoin(tmp_directory_path(), ft_strdup(".heredoc_tmp_"));
	ft_strcat(&ret, ft_itoa(g_var->here_doc_cnt / 10));
	ft_strcat(&ret, ft_itoa(g_var->here_doc_cnt % 10));
	return (ret);
}

static char	*tmp_directory_path(void)
{
	t_list	*cur;

	cur = g_var->env_list;
	while (cur)
	{
		if (ft_strncmp(cur->content, "TMPDIR=", 7) == 0)
			return (ft_strdup(cur->content + 7));
		cur = cur->next;
	}
	return (ft_strdup(""));
}

static t_bool	convert_expand(char **line)
{
	const char	*exp = ft_strchr(*line, '$');
	char		*res;

	if (exp == NULL)
		return (TRUE);
	res = ft_substr(*line, 0, exp - *line);
	ft_strcat(&res, expand(&exp));
	ft_strcat(&res, exp + 1);
	free(*line);
	*line = res;
	return (TRUE);
}
