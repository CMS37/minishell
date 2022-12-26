#include "../../incs/subsystem.h"

/*
strerror에 에러넘버에따라 정의가되지만 위에 4가지는 따로 핸들링 해줘야함
strerror은 0~107까지 에러넘버에따라 메세지 내장되있음
----
exit_status(cmd, token->value, strerror(errno));
->strerror에 정의된 에러코드면 일케

exit_status(cmd, token->value, ARG_ERR);
->안된건 이렇게
*/

void	exit_status(char *cmd, char *value, char *err_str)
{
	printf("minishell: %s", cmd);
	if (value != NULL)
		printf(": %s", value);
	if (err_str != NULL)
		printf(": %s", err_str);
	printf("\n");
}

/*
0	성공적으로 실행	
1	광범위한 일반적 에러	“Operation not permitted” , "not a valid identifier", "too many arguments" 등
2	쉘 builtin 명령어의 오사용	“No such file or directory” 등
126	Permission 문제로 실행 불가능한 명령어의 구동	"Permission denied", "Is a directory"
127	명령어의 경로($PATH) 문제 혹은 명령어 오타	“Command not found”, “No such file or directory”
130	치명적 에러 발생으로 인한 종료 (Ctrl+C)	"Script terminated by Ctrl+C”
255	exit 에 정수(0~255)가 아닌 인자 넘김	"numeric argument required"
*/