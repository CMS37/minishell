#include "../../incs/utils.h"
#include "../../incs/structs.h"
#include <unistd.h>

char	*home_dir(void);
char	*convert_relative_path_to_absolute_path(const char *path);

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

char	*convert_relative_path_to_absolute_path(const char *path)
{
	char	*ret;

	if (*path == '/')
		return (ft_strdup(path));
	if (*path == '~')
		ret = home_dir();
	else
		ret = getcwd(NULL, 0);
	if (ret == NULL)
		return (NULL);
	ft_strcat(&ret, "/");
	ft_strcat(&ret, path);
	return (ret);
}
