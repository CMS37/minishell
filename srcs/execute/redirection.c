/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:36 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/09 14:49:06 by younhwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute.h"
#include "../../incs/lexer.h"
#include "../../incs/builtin.h"
#include "../../incs/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

t_bool		set_fd_in_redir(t_list **token_list);
int			open_file(const char *file, t_open_flag flag);
static int	get_fd(t_list *token_list);
t_bool		rm_tokens(t_list **token_list);
t_bool		rm_token(t_list *token_list);

t_bool	set_fd_in_redir(t_list **token_list)
{
	int		fd;
	t_list	*cur;

	cur = *token_list;
	while (cur)
	{
		fd = get_fd(cur);
		if (fd == -1)
			return (FALSE);
		if (0 < fd)
		{
			if (ft_strcmp(((t_token *) cur->content)->value, "<") == 0 || \
				ft_strcmp(((t_token *) cur->content)->value, "<<") == 0)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
			cur = cur->next;
		}
		cur = cur->next;
	}
	return (rm_tokens(token_list));
}

static int	get_fd(t_list *token_list)
{
	t_token *const	cur = token_list->content;
	t_token			*next;
	int				ret;

	ret = 0;
	if (token_list->next == NULL)
		return (ret);
	next = token_list->next->content;
	if (cur->type != T_REDIRECT)
		return (ret);
	if (ft_strcmp(cur->value, "<") == 0)
		ret = open_file(next->value, FILE_IN);
	else if (ft_strcmp(cur->value, "<<") == 0)
	{
		ret = open_file(next->value, FILE_IN);
		unlink(next->value);
	}
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
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == FILE_OUT_TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == FILE_IN)
		fd = open(file, O_RDONLY, 0777);
	else if (flag == FILE_OUT_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		if (flag == HERE_DOC || flag == FILE_OUT_TRUNC)
			perror("Error");
		if (flag == FILE_OUT_TRUNC)
			exit(set_exit_status(errno));
		if (flag == FILE_IN)
			print_err(1, (char *) file, NULL, EXIST_ERR);
	}
	return (fd);
}

t_bool	rm_tokens(t_list **token_list)
{
	t_list	*prev;
	t_list	*cur;

	prev = NULL;
	cur = *token_list;
	while (cur)
	{
		while (((t_token *) cur->content)->type == T_REDIRECT)
		{
			if (rm_token(cur) == FALSE)
			{
				if (prev == NULL)
					*token_list = NULL;
				else
					prev->next = NULL;
				return (*token_list != NULL);
			}
		}
		prev = cur;
		cur = cur->next;
	}
	return (TRUE);
}

t_bool	rm_token(t_list *token_list)
{
	t_list *const	next_token = token_list->next->next;

	ft_lstdelone(token_list->next, del_token);
	if (next_token == NULL)
	{
		ft_lstdelone(token_list, del_token);
		return (FALSE);
	}
	del_token(token_list->content);
	token_list->content = next_token->content;
	token_list->next = next_token->next;
	free(next_token);
	return (TRUE);
}
