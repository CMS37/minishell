#include "../../incs/subsystem.h"

t_bool	exit_status(char *cmd, char *value, char *err_str);
t_bool	set_exit_status(int status);

t_bool	exit_status(char *cmd, char *value, char *err_str)
{
	printf("minishell: %s", cmd);
	if (value != NULL)
	{
		printf(": %s", value);
		if (err_str != NULL)
			printf(": %s", err_str);
	}
	printf("\n");
	return (TRUE);
}

t_bool	set_exit_status(int status)
{
	g_var->exit_status = status;
	return (TRUE);
}

/*
0	성공적으로 실행	
1	광범위한 일반적 에러	“Operation not permitted” , "not a valid identifier", "too many arguments" 등
2	쉘 builtin 명령어의 오사용	“No such file or directory” 등
126	Permission 문제로 실행 불가능한 명령어의 구동	"Permission denied", "Is a directory"
127	명령어의 경로($PATH) 문제 혹은 명령어 오타	“Command not found”, “No such file or directory”
130	치명적 에러 발생으로 인한 종료 (Ctrl+C)	"Script terminated by Ctrl+C”
255	exit 에 정수(0~255)가 아닌 인자 넘김	"numeric argument required"
->근데 bash에선 255넘을때마다 다시 0부터 카운트하고 최대 LLONG사이즈까지 반복
->그 이상이오면 그떄서야 에러

Bash는 값 128+ N 을 종료 상태로 사용합니다.
명령을 찾을 수 없는 경우 이를 실행하기 위해 생성된 자식 프로세스는 상태 127을 반환합니다. 명령을 찾았지만 실행할 수 없는 경우 반환 상태는 126입니다.

strerror에 에러넘버에따라 정의가되지만 107이상의 에러넘버는 따로 핸들링 해줘야함
strerror은 0~107까지 에러넘버에따라 메세지 내장되있음
*/