# minishell
### As beautiful as a shell
<br/><br/>

## Summary
#### This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.
<br/><br/><br/>

## Install
	$ make (all)
<br/><br/><br/>

## Usage
	$ ./minishell

### Supported tokens
	- `|` (pipe)
	- `<` (redirect input)
	- `>` (redirect output)
	- `>>` (redirect output with append)
	- `<<` (heredoc)
	- `'` (single quote)
	- `"` (double quote)
	- `$` (variable: only `$?`, `$_` and environment variables)

### builtin commands
	- `cd`
	- `echo`
	- `env`
	- `exit`
	- `export`
	- `pwd`
	- `unset`