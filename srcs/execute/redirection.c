#include "../../libs/libft/incs/libft.h"
#include "../../incs/execute.h"
#include "../../incs/structs.h"
#include "../../incs/lexer.h"
#include "../../incs/subsystem.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

t_bool		set_fd_in_redir(t_list *token_list);
static int	get_fd(t_list *token_list);
int			open_file(const char *file, t_open_flag flag);
t_bool		rm_tokens(t_list *token_list);
t_bool		rm_token(t_list *token_list);

t_bool	set_fd_in_redir(t_list *token_list)
{
	int		fd;
	t_list	*cur;

	cur = token_list;
	while (cur)
	{
		fd = get_fd(cur);
		if (fd == -1)
			return (!set_exit_status(1));
		if (0 < fd)
		{
			if (ft_strcmp(((t_token *) cur->content)->value, "<") == 0)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
			cur = cur->next;
		}
		cur = cur->next;
	}
	rm_tokens(token_list);
	return (TRUE);
}

static int	get_fd(t_list *token_list)
{
	int		ret;
	t_token	*cur;
	t_token	*next;

	ret = 0;
	cur = token_list->content;
	if (token_list->next == NULL)
		return (ret);
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

	fd = -1;
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
			ft_putstr_fd("Error: No such file or directory: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	return (fd);
}

t_bool	rm_tokens(t_list *token_list)
{
	t_list	*prev;
	t_list	*cur;

	prev = NULL;
	cur = token_list;
	while (cur)
	{
		while (ft_strcmp(((t_token *) cur->content)->value, "<") == 0 || \
			ft_strcmp(((t_token *) cur->content)->value, ">") == 0 || \
			ft_strcmp(((t_token *) cur->content)->value, ">>") == 0)
		{
			if (rm_token(cur) == FALSE)
			{
				prev->next = NULL;
				free(cur);
				return (TRUE);
			}
		}
		prev = cur;
		cur = cur->next;
	}
	return (TRUE);
}

t_bool		rm_token(t_list *token_list)
{
	t_list *const	next_token = token_list->next->next;

	ft_lstdelone(token_list->next, del_token);
	del_token(token_list->content);
	if (next_token == NULL)
		return (FALSE);
	token_list->content = next_token->content;
	token_list->next = next_token->next;
	free(next_token);
	return (TRUE);
}
