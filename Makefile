SHELL	= /bin/bash
SPINNER	= /-\|/
IDX		= 0

NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= 
AR		= ar rcs
RM		= rm -f

FT_PRINTF_DIR	= ./libs/ft_printf
GNL_DIR			= ./libs/get_next_line
FT_PRINTF	:= ${FT_PRINTF_DIR}/libftprintf.a
GNL			:= ${GNL_DIR}/libgnl.a
LIBS		= ${FT_PRINTF} ${GNL}

INCS_DIR	= ./incs
SRCS_DIR	= ./srcs
OBJS_DIR	= ./objs

SRCS = 	minishell.c\
		execute/execute.c
		lexer/lexer.c\
		lexer/tokenizer.c\
		parser/parser.c\
		subsystem/subsystem.c
		
SRCS := ${addprefix ${SRCS_DIR}/, ${SRCS}}
OBJS := ${SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o}


all: ${NAME}


${OBJS_DIR}:
	@echo "Build ${NAME}"
	@mkdir -p ${OBJS_DIR}
	@mkdir -p ${OBJS_DIR}/execute
	@mkdir -p ${OBJS_DIR}/lexer
	@mkdir -p ${OBJS_DIR}/parser
	@mkdir -p ${OBJS_DIR}/subsystem


${FT_PRINTF}:
	@make -C ${FT_PRINTF_DIR}


${GNL}:
	@make -C ${GNL_DIR}


${NAME}: ${OBJS}
	@printf "\bdone\n"
	@make -C ${FT_PRINTF_DIR}
	@make -C ${GNL_DIR}
	${eval IDX = 0}
	@${CC} ${LDFLAGS} -g -o ${NAME} ${OBJS} ${LIBS} -I ${INCS_DIR}
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
	@${CC} ${CFLAGS} -g -c $< -o $@ -I ${INCS_DIR}


clean:
	@echo "Remove dependencies in ${NAME}"
	@make -C ${FT_PRINTF_DIR} clean
	@make -C ${GNL_DIR} clean
	@rm -rf ${OBJS_DIR}


fclean:
	@echo "Remove dependencies in ${NAME}"
	@make -C ${FT_PRINTF_DIR} fclean
	@make -C ${GNL_DIR} fclean
	@echo "Remove ${NAME}"
	@rm -rf ${OBJS_DIR}
	@${RM} ${NAME}
	

re:
	@echo "Re-build ${NAME}"
	@make fclean
	@make all


.PHONY: all clean fclean re bonus