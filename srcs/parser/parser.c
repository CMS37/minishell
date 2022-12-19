#include "../../incs/minishell.h"

/*
lexer 에서 들어온 문자열 토큰화 후 전달 -> 구조체로 리턴받을듯?

구조체 받아서 오류 검사 후 파싱트리?

<cmd>
<option>
<argv>
<pipe>

pipeline         :      pipe_sequence
                 | Bang pipe_sequence
                 ;
pipe_sequence    :                             command
                 | pipe_sequence '|' linebreak command
                 ;
command          : simple_command
                 | compound_command
                 | compound_command redirect_list
                 | function_definition
                 ;
compound_command : brace_group
                 | subshell
                 | for_clause
                 | case_clause
                 | if_clause
                 | while_clause
                 | until_clause
                 ;

*/

void    parsing(void)
{
    
}