#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

t_bool			here_docs(void);
static t_bool	here_doc(char **token);
static char		*generate_file_name(void);
static char		*tmp_directory_path(void);

t_bool	here_docs(void)
{
	t_list	*cur;
	char	**tokens;

	cur = g_var->cmd_list;
	while (cur)
	{
		tokens = cur->content;
		while (*tokens)
		{
			if (ft_strcmp(*tokens, "<<") == 0)
			{
				g_var->here_doc_cnt++;
				if (here_doc(tokens++) == FALSE)
					return (FALSE);
			}
			tokens++;
		}
		cur = cur->next;
	}
	return (TRUE);
}

static t_bool	here_doc(char **token)
{
	int			fd;
	char		*line;
	char *const	file_name = generate_file_name();

	free(*token);
	*token = ft_strdup("<");
	fd = open_file(file_name, HERE_DOC);
	while (TRUE)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			return (FALSE);
		if (ft_strcmp(line, *(token + 1)) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	free(*(token + 1));
	*(token + 1) = file_name;
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
