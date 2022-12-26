SHELL	= /bin/bash
SPINNER	= /-\|/
IDX		= 0

NAME	= minishell

READLINE_DIR	= ${HOME}/.brew/opt/readline
READLINE_INCS	= ${READLINE_DIR}/include

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -L${READLINE_DIR}/lib -lreadline
AR		= ar rcs
RM		= rm -f

LIBS_DIR	= ./libs
LIBFT_DIR	:= ${LIBS_DIR}/libft
LIBFT		:= ${LIBFT_DIR}/libft.a
LIBS		:= ${LIBFT}

INCS_DIR	= ./incs
SRCS_DIR	= ./srcs
OBJS_DIR	= ./objs

SRCS = 	minishell.c \
		builtin/env.c \
		builtin/export.c \
		builtin/pwd.c \
		builtin/unset.c \
		execute/execute.c \
		execute/exec_builtin.c \
		execute/exec_extern.c \
		execute/here_docs.c \
		execute/list_to_arr.c \
		execute/redirection.c \
		lexer/lexer.c \
		lexer/handle_quote.c \
		lexer/token.c \
		lexer/tokenizer.c \
		parser/parser.c \
		parser/parser_utils.c \
		parser/check_quotes.c \
		parser/syntax_err.c \
		parser/check_word.c \
		parser/check_unexpected_token.c \
		parser/create_cmd_list.c \
		subsystem/signal.c \
		subsystem/subsystem.c \
		subsystem/termios.c
		
SRCS := ${addprefix ${SRCS_DIR}/, ${SRCS}}
OBJS := ${SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o}


all: ${NAME}


${OBJS_DIR}:
	@echo "Build ${NAME}"
	@mkdir -p ${OBJS_DIR}
	@mkdir -p ${OBJS_DIR}/builtin
	@mkdir -p ${OBJS_DIR}/execute
	@mkdir -p ${OBJS_DIR}/lexer
	@mkdir -p ${OBJS_DIR}/parser
	@mkdir -p ${OBJS_DIR}/subsystem


${LIBFT}:
	@make -C ${LIBFT_DIR}


${NAME}: ${LIBFT} ${OBJS}
	@printf "\bdone\n"
	${eval IDX = 0}
	@${CC} ${LDFLAGS} -g -o ${NAME} ${OBJS} ${LIBS}
	@echo "Build ${NAME}: done"


${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	${eval IDX = ${shell expr ${IDX} + 1}}
	${eval T_IDX = ${shell expr ${IDX} % 32}}
	${eval T_IDX = ${shell expr ${T_IDX} / 8 + 1}}
	${eval CHR = ${shell echo ${SPINNER} | cut -c ${T_IDX}}}
	@if [ ${IDX} = 1 ]; then\
		echo -n "Build dependencies in ${NAME} ...  ";\
	fi
	@printf "\b${CHR}"
	@${CC} ${CFLAGS} -g -c $< -o $@ -I${INCS_DIR} -I${READLINE_INCS}


clean:
	@echo "Remove dependencies in ${NAME}"
	@make -C ${LIBFT_DIR} clean
	@rm -rf ${OBJS_DIR}


fclean:
	@echo "Remove dependencies in ${NAME}"
	@make -C ${LIBFT_DIR} fclean
	@echo "Remove ${NAME}"
	@rm -rf ${OBJS_DIR}
	@${RM} ${NAME}
	

re:
	@echo "Re-build ${NAME}"
	@make fclean
	@make all


.PHONY: all clean fclean re bonus