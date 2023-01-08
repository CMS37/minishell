SHELL	= /bin/bash
SPINNER	= /-\|/
IDX		= 0

NAME	= minishell

READLINE_DIR		= ${HOME}/.brew/opt/readline
READLINE_INCS_DIR	= ${READLINE_DIR}/include

LIBS_DIR		= ./libs
LIBFT_DIR		:= ${LIBS_DIR}/libft
LIBFT_INCS_DIR	:= ${LIBFT_DIR}/incs
LIBFT			:= ${LIBFT_DIR}/libft.a

INCS_DIR	= ./incs
SRCS_DIR	= ./srcs
OBJS_DIR	= ./objs

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I${INCS_DIR} -I${LIBFT_INCS_DIR} -I${READLINE_INCS_DIR} -MD
LDFLAGS	= -L${READLINE_DIR}/lib -lreadline -L${LIBFT_DIR} -lft
AR		= ar rcs
RM		= rm -f

SRCS = 	minishell.c \
		builtin/cd.c \
		builtin/echo.c \
		builtin/env.c \
		builtin/exit.c \
		builtin/export.c \
		builtin/pwd.c \
		builtin/unset.c \
		execute/execute.c \
		execute/exec_builtin.c \
		execute/exec_extern.c \
		execute/redirection.c \
		lexer/lexer.c \
		lexer/expand.c \
		lexer/ifs.c \
		lexer/meta.c \
		lexer/quote.c \
		lexer/token.c \
		lexer/tokenizer.c \
		parser/parser.c \
		parser/create_cmd_list.c \
		parser/here_doc.c \
		parser/syntax_err_occurred.c \
		subsystem/subsystem.c \
		subsystem/signal.c \
		subsystem/termios.c \
		utils/convert_path.c \
		utils/ft_getenv.c \
		utils/path.c \
		utils/print_err.c
		
SRCS := ${addprefix ${SRCS_DIR}/, ${SRCS}}
OBJS := ${SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o}
DEPS := ${OBJS:.o=.d}

all: ${NAME}


${OBJS_DIR}:
	@echo "Build ${NAME}"
	@mkdir -p ${OBJS_DIR}
	@mkdir -p ${OBJS_DIR}/builtin
	@mkdir -p ${OBJS_DIR}/execute
	@mkdir -p ${OBJS_DIR}/lexer
	@mkdir -p ${OBJS_DIR}/parser
	@mkdir -p ${OBJS_DIR}/subsystem
	@mkdir -p ${OBJS_DIR}/utils


${LIBFT}:
	@make -C ${LIBFT_DIR}


${NAME}: ${LIBFT} ${OBJS}
	@printf "\bdone\n"
	${eval IDX = 0}
	@${CC} ${LDFLAGS} -g -o ${NAME} ${OBJS}
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
	@${CC} ${CFLAGS} -g -c $< -o $@


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

-include ${DEPS}