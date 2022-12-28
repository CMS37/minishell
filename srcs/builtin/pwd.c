#include "../../libs/libft/incs/libft.h"
#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/subsystem.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int	builtin_pwd(t_list *token_list, int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		exit_status("pwd", strerror(errno), NULL);
		return (1);
	}
	ft_putendl_fd(pwd, fd);
	free(pwd);
	g_var->exit_status = 0;
	(void) token_list;
	return (0);
}

/*
getcwd에서 NULL을 리턴 시 errno가 ERANGE로 설정 -> getcwd manual
ERANGE = 결과가 너무 큽니다. 
		 수학 함수의 인수가 너무 커서 결과에서 중요 전체 또는 부분 손실이 발생했습니다. 
		 인수가 예상보다 큰 경우(예 buffer_getcwd : 인수가 예상보다 긴 경우) 다른 함수에서도 이 오류가 발생할 수 있습니다.
*/