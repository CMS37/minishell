#include "../../incs/builtin.h"
#include "../../incs/lexer.h"

void			set_pwd(int fd);
static t_list	*ft_env_pwd(int i);

void	set_pwd(int fd)
{
	t_list	*new_token;
	int		i;

	i = 0;
	while(++i < 3)
	{
		new_token = ft_env_pwd(i);
		builtin_export(new_token, fd);
		free(new_token);
	}
}

static t_list *ft_env_pwd(int i)
{	
	char	*pwd;
	t_list	*tmp;
	t_list	*env;

	env = g_var->env_list;
	tmp = init_token();
	ft_strncat(&tmp->content, "export", 1);
	pwd = NULL;
	while (i == 1 && env)
	{
		if (ft_strnstr(tmp->content, "PWD=", 4) != 0)
		{
			pwd = ft_strjoin("OLD_PWD=", tmp->content + 4);
			break;
		}
		env = env->next;
	}
	if (i == 2)
		pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	tmp2 = init_token();
	ft_strncat(&tmp->content, pwd, 1);
	ft_lstadd_back(&tmp, ft_lstnew(tmp2));
	if (pwd)
		free(pwd);
	return (tmp);
}