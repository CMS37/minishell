#include "../../incs/parser.h"
#include "../../incs/structs.h"


int	find_cmd(char *value)
{
	while()
	{
		//패치경로 :구분자로 돌면서 있는지 검사
		//있으면 리턴1
		return (1);
	}
	//나오면 패치경로다봐도 없으니 인자로판단 리턴2
	//인자의 유효성 검사는 execve에서 처리
	return (2);
}

int	find_red(char *value)
{
	if (ft_strcmp(value,">"));
		return (1);
	ft_strcmp(value,">>");
		return (2);
	ft_strcmp(value,"<");
		return (3);
	ft_strcmp(value,"<<");
		return (4);
}

t_list *check_word_type(t_list *list)
{
	t_list	*tmp;
	t_token	*token;
	int		i;
	
	tmp = list;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		if (token->type == T_WORD)
		{
			if (find_cmd(token->value))
				token->type = T_CMD;
			else
				token->type = T_ARGV;
		}
		else if (token->type == T_REDIRECT)
		{
			i = find_red(token->value)
			if (i == 1)
				token->type = T_RED_R;
			else if (i == 2)
				token->type = T_RED_RR;
			else if (i == 3)
				token->type = T_RED_L;
			else
				token->type = T_RED_LL;
		}
		tmp = tmp->next;
	}
	return (list);
}