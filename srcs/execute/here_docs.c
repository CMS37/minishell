#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

t_bool			here_docs(void);
static t_bool	here_doc(t_list *cmd);
static char		*generate_file_name(void);
static char		*tmp_directory_path(void);

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
			if (ft_strcmp(((t_token *) cur_cmd->content)->value, "<<"))
			{
				if (!here_doc(cur_cmd))
					return (FALSE);
			}
			cur_cmd = cur_cmd->next;
		}
		cmd_list_tmp = cmd_list_tmp->next;
	}
	return (TRUE);
}

static t_bool	here_doc(t_list *cmd)
{
	int			fd;
	char		*line;
	char *const	file_name = generate_file_name();

	free(((t_token *) cmd->content)->value);
	((t_token *) cmd->content)->value = ft_strdup("<");
	fd = open_file(file_name, HERE_DOC);
	while (TRUE)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			return (FALSE);
		if (ft_strcmp(line, ((t_token *) cmd->next->content)->value) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	free(((t_token *) cmd->next->content)->value);
	((t_token *) cmd->next->content)->value = file_name;
	close(fd);
	return (TRUE);
}

static char	*generate_file_name(void)
{
	char	*ret;

	ret = ft_strjoin(tmp_directory_path(), ft_strdup(".heredoc_tmp_"));
	ret = ft_strjoin(ret, ft_itoa(g_var->here_doc_cnt / 10));
	ret = ft_strjoin(ret, ft_itoa(g_var->here_doc_cnt % 10));
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
