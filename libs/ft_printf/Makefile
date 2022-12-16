# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: younhwan <younhwan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 16:03:07 by younhwan          #+#    #+#              #
#    Updated: 2022/09/18 13:22:30 by younhwan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL	= /bin/bash
SPINNER	= /-\|/
IDX		= 0

NAME = libftprintf.a

LIBFT_DIR = libft
LIBFT_NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

INCS_DIR = ./includes

SRCS_DIR = ./srcs
OBJS_DIR = ./objs

#SRCS_BONUS_DIR = ./srcs_bonus
#OBJS_BONUS_DIR = ./objs_bonus

SRCS = 	ft_print_char.c \
		ft_print_hex.c \
		ft_print_nbr.c \
		ft_print_ptr.c \
		ft_print_str.c \
		ft_print_unsigned_int.c \
		ft_printf.c

#SRCS_BONUS = 

SRCS := ${addprefix ${SRCS_DIR}/, ${SRCS}}
#SRCS_BONUS := ${addprefix ${SRC_BONUS_DIR}/, ${SRC_BONUS}}

OBJS = ${SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o}
#OBJS_BONUS = ${SRC_BONUS:${SRC_BONUS_DIR}/%.c=${OBJ_BONUS_DIR}/%.o}

ifdef WITH_BONUS
	OBJ_FILES = ${OBJS} ${OBJS_BONUS}
	OBJS_DIRS = ${OBJS_DIR} ${OBJS_BONUS_DIR}
else
	OBJ_FILES = ${OBJS}
	OBJS_DIRS = ${OBJS_DIR}
endif

#bonus:
#	WITH_BONUS=1 make all

all: ${OBJS_DIRS}
	@make ${NAME}

# ${OBJS_BONUS_DIR}:
# 	mkdir -p objs_bonus

${OBJS_DIR}:
	@echo "Build libftprintf.a"
	@mkdir -p objs

${OBJ_FILES}: %.o: ${addsuffix .c,${subst obj,src,${%}}}
	${eval IDX = ${shell expr ${IDX} + 1}}
	${eval T_IDX = ${shell expr ${IDX} % 32}}
	${eval T_IDX = ${shell expr ${T_IDX} / 8 + 1}}
	${eval CHR = ${shell echo ${SPINNER} | cut -c ${T_IDX}}}
	@if [ ${IDX} = 1 ]; then echo -n "Build dependencies in libftprintf.a ...  "; fi
	@printf "\b${CHR}"
	@${CC} ${CFLAGS} -c ${patsubst %.o,%.c,${subst obj,src,$@}} -o $@ -I ${INCS_DIR}

${NAME}: ${OBJ_FILES}
	@printf "\bdone\n"
	@make -C ${LIBFT_DIR}
	@cp ${LIBFT_DIR}/${LIBFT_NAME} .
	@mv ${LIBFT_NAME} ${NAME}
	@${AR} $@ $^
	@echo "Build libftprintf.a: done"

clean:
	@echo "Remove dependencies in ft_printf"
	@make -C ${LIBFT_DIR} clean
	@rm -rf ${OBJS_DIR}
#	rm -rf ${OBJS_BONUS_DIR}

fclean:
	@echo "Remove dependencies in ft_printf"
	@make -C ${LIBFT_DIR} fclean
	@echo "Remove libftprintf.a"
	@rm -rf ${OBJS_DIR}
	@${RM} ${NAME}

re:
	@echo "Re-build libftprintf.a"
	@make fclean
	@make all

.PHONY: all clean fclean re #bonus