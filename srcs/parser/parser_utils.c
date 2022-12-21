#include "../../incs/minishell.h"
#include <stdlib.h>

/*
	T_PIPE = 2,
	T_REDIRECT = 3,
	T_SINGLE_QUOTE = 4,
	T_DOUBLE_QUOTE = 5,
*/

t_bool	is_unexpected_token(const char *token);
int		next_pipe(t_list *list);
int		all_pipe(t_list *list);
void	free_cmd(char **cmd);

t_bool	is_unexpected_token(const char *token)
{
	if (!ft_strcmp(token, "|"))
		return (TRUE);
	if (!ft_strcmp(token, ">") || !ft_strcmp(token, "<"))
		return (TRUE);
	if (!ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
		return (TRUE);
	if (!ft_strcmp(token, "'") || !ft_strcmp(token, "\""))
		return (TRUE);
	return (FALSE);
}

int	next_pipe(t_list *list)
{
	int		pipe_idx;
	t_list	*tmp;
	t_token	*token;

	tmp = list;
	pipe_idx = 0;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		if (!ft_strcmp(token->value, "|"))
			break ;
		pipe_idx++;
		tmp = tmp->next;
	}
	return (pipe_idx);
}

int	all_pipe(t_list *list)
{
	int		num_of_pipe;
	t_list	*tmp;
	t_token	*token;

	tmp = list;
	num_of_pipe = 0;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		if (!ft_strcmp(token->value, "|"))
			num_of_pipe++;
		tmp = tmp->next;
	}
	return (num_of_pipe);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = -1;
	while(cmd[++i])
		free(cmd[i]);
	return;
}