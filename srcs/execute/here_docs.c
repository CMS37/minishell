#include "../../libs/libft/incs/libft.h"
#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include "../../incs/lexer.h"
#include "../../incs/builtin.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

t_bool			here_docs(void);
static t_bool	here_doc(t_list *token_list);
static char		*generate_file_name(void);
static char		*tmp_directory_path(void);
static t_bool	convert_expand(char **line);

t_bool	here_docs(void)
{
	t_list	*cmd_list_tmp;
	t_list	*cur_cmd;

	cmd_list_tmp = g_var->cmd_list;
	while (cmd_list_tmp)
	{
		cur_cmd = cmd_list_tmp->content;
		while (cur_cmd)
		{
			if (ft_strcmp(((t_token *) cur_cmd->content)->value, "<<") == 0)
				if (here_doc(cur_cmd) == FALSE)
					return (FALSE);
			cur_cmd = cur_cmd->next;
		}
		cmd_list_tmp = cmd_list_tmp->next;
	}
	return (TRUE);
}

static t_bool	here_doc(t_list *token_list)
{
	char *const	file_name = generate_file_name();
	const int	fd = open_file(file_name, HERE_DOC);
	char		*line;

	if (fd == -1)
		return (set_exit_status(errno) == 0);
	while (TRUE)
	{
		line = readline("heredoc> ");
		if (line == NULL ||
			!ft_strcmp(line, ((t_token *) token_list->next->content)->value))
			break ;
		convert_expand(&line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	free(((t_token *) token_list->next->content)->value);
	((t_token *) token_list->next->content)->value = file_name;
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
	char	 	*res;

	if (exp == NULL)
		return (TRUE);
	res = ft_substr(*line, 0, exp - *line);
	ft_strcat(&res, expand(&exp));
	ft_strcat(&res, exp + 1);
	free(*line);
	*line = res;
	return (TRUE);
}
