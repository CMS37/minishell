#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include "../../incs/lexer.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

t_bool		set_fd_in_redir(t_list **token_list);
static int	get_fd(t_list *token_list);
int			open_file(const char *file, t_open_flag flag);
t_bool		rm_tokens(t_list *prev, t_list *cur, t_list **token_list);

t_bool	set_fd_in_redir(t_list **token_list)
{
	int		fd;
	t_list	*prev;
	t_list	*cur;

	prev = NULL;
	cur = (*token_list);
	while (cur)
	{
		fd = get_fd(cur);
		if (fd != -1)
		{
			if (ft_strcmp(((t_token *) cur->content)->value, "<") == 0)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
			rm_tokens(prev, cur, token_list);
		}
		else
			cur = cur->next;
		prev = cur;
	}
	return (TRUE);
}

static int	get_fd(t_list *token_list)
{
	int		ret;
	t_token	*cur;
	t_token	*next;

	ret = -1;
	cur = token_list->content;
	next = token_list->next->content;
	if (ft_strcmp(cur->value, "<") == 0)
		ret = open_file(next->value, FILE_IN);
	else if (ft_strcmp(cur->value, ">") == 0)
		ret = open_file(next->value, FILE_OUT_TRUNC);
	else if (ft_strcmp(cur->value, ">>") == 0)
		ret = open_file(next->value, FILE_OUT_APPEND);
	return (ret);
}

int	open_file(const char *file, t_open_flag flag)
{
	int	fd;

	fd = 0;
	if (flag == HERE_DOC)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (flag == FILE_OUT_TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == FILE_IN)
		fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
	{
		if (flag == HERE_DOC || flag == FILE_OUT_TRUNC)
			perror("\033[31mError");
		if (flag == FILE_OUT_TRUNC)
			exit(EXIT_FAILURE);
		if (flag == FILE_IN)
		{
			ft_putstr_fd("\033[31mError: No such file or directory: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd("\033[m\n", 2);
		}	
	}
	return (fd);
}

t_bool		rm_tokens(t_list *prev, t_list *cur, t_list **token_list)
{
	if (cur != (*token_list))
		prev->next = cur->next->next;
	else
		*token_list = cur->next->next;
	del_token(cur->next->content);
	free(cur->next);
	del_token(cur->content);
	free(cur);
	return (TRUE);
}
