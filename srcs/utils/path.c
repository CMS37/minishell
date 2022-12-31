#include "../../incs/utils.h"
#include "../../incs/structs.h"
#include <unistd.h>
#include <stdlib.h>

char	*home_dir(void);
t_bool	convert_to_absolute_path(char **path);

char	*home_dir(void)
{
	t_list	*tmp;

	tmp = g_var->env_list;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, "HOME=", 5) != 0)
			return (ft_strdup(tmp->content + 5));
		tmp = tmp->next;
	}
	return (NULL);
}

t_bool	convert_to_absolute_path(char **path)
{
	char	*ret;

	if (**path == '~')
	{
		ret = home_dir();
		ft_strcat(&ret, *path + 1);
		free(*path);
		*path = ret;
		return (TRUE);
	}
	if (**path == '\0' || **path == '/' || ft_strchr(*path, '/') == NULL)
		return (TRUE);
	ret = getcwd(NULL, 0);
	if (ret == NULL)
		return (FALSE);
	ft_strcat(&ret, "/");
	ft_strcat(&ret, *path);
	free(*path);
	*path = ret;
	return (TRUE);
}
