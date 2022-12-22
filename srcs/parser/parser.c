#include "../../incs/parser.h"

void	parsing(void);
void	del_cmd(void *cmd);

void	parsing(void)
{
	// TODO: handle quotes
	if (check_syntax_err())
		return ;
	check_unexpected_token();
	ft_lstclear(&g_var->cmd_list, del_cmd);
	create_cmd_list();
	return ;
}

void	del_cmd(void *cmd)
{
	t_list	*t_cmd;

	t_cmd = (t_list *) cmd;
	ft_lstclear(&t_cmd, del_token);
}

/*
int	operation_word(t_cmd **cmd, char *line, int *index)
{
	if (!ft_strncmp(&line[*index], "<", 1))
		parsing_left(line, cmd, index);
	else if (!ft_strncmp(&line[*index], ">", 1))
		parsing_right(line, cmd, index);
	else if (!ft_strncmp(&line[*index], "|", 1))
	{
		if (line[(*index) + 1] == '|')
			return (1);
		else
			insert_node(cmd, PIPE, ft_strdup("|"));
	}
	else if (!ft_strncmp(&line[*index], "$", 1))
		insert_node(cmd, DOLR, ft_strdup("$"));
	return (0);
}
void	argument_word(t_cmd **cmd, char *line, int *index)
{
	int		tmp;
	char	*str;

	tmp = *index;
	while (line[*index] && line[*index] != ' ' && line[*index] != '<' \
		&& line[*index] != '>' && line[*index] != '|' && line[*index] != ';' \
		&& line[*index] != '\"' && line[*index] != '\'' \
		&& line[*index] != '\\' && line[*index] != '$')
		(*index)++;
	if (*index - tmp)
	{
		str = ft_substr(line, tmp, *index - tmp);
		insert_node(cmd, ARG, str);
	}
	(*index)--;
}

void	error(char	*str)
{
	// TODO: set exit_status: 258
	printf("minishell: syntax error near unexpected token `%s\'\n", str);
}

*/

