# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 16:40:26 by thzimmer          #+#    #+#              #
#    Updated: 2019/09/12 15:49:35 by lzimmerm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, libft, $(NAME), $(NAME2)

# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #


NAME       = corewar
SRCS_PATH  = srcs/corewar/
OBJS_PATH  = objs/corewar/
SRC_NAME   = main.c init.c parser.c game.c read_short_int.c get_param.c op.c \
             op_1.c op_2.c op_3.c viewer.c
OBJ_NAME   = $(SRC_NAME:.c=.o)
SRCS       = $(addprefix $(SRCS_PATH),$(SRC_NAME))
OBJS       = $(addprefix $(OBJS_PATH),$(OBJ_NAME))
HEADERS    = libft/libft.a includes/op.h includes/corewar.h

NAME2      = asm
SRCS2_PATH = srcs/asm/
OBJS2_PATH = objs/asm/
SRC2_NAME  = op.c main.c usage.c file_checker.c instructions.c \
             operation_recognition.c arguments.c args_byting.c checker.c \
             args_utils.c labels.c lexer.c get_arg_value.c free.c \
             operations1.c operations2.c operations3.c update_labels.c \
             start_bytes_writing.c exec_bytes_writing.c print_instructions.c \

OBJ2_NAME  = $(SRC2_NAME:.c=.o)
SRCS2      = $(addprefix $(SRCS2_PATH),$(SRC2_NAME))
OBJS2      = $(addprefix $(OBJS2_PATH),$(OBJ2_NAME))
HEADERS2   = libft/libft.a includes/op.h includes/asm.h

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all           : $(NAME) $(NAME2)

CC            = gcc
CFLAGS        = -Wall -Wextra -Werror

libft         : libft/libft.a

libft/libft.a : FORCE
	@make -C libft

FORCE         :

clean         :
	@rm -rf objs
	@make clean -sC libft
	@printf "make: objs cleaned\\n"

fclean        : clean
	@rm -rf $(NAME) $(NAME2)
	@make fclean -sC libft
	@printf "make: programs cleaned\\n"

re            : fclean all

# **************************************************************************** #
#                                COMPILATION                                   #
# **************************************************************************** #

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c Makefile $(HEADERS)
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[K"
	@printf "make: compiling $<\\r"

$(NAME)         : $(OBJS)
	@printf "\033[K"
	@$(CC) $(CFLAGS) $^ -o $(NAME) -L libft -lft -lcurses
	@printf "\033[37;1m-- $(NAME)     [ \033[32;1mOK\033[37;1m ]\033[0m\\n"

$(OBJS2_PATH)%.o : $(SRCS2_PATH)%.c Makefile $(HEADERS2)
	@mkdir -p $(OBJS2_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[K"
	@printf "make: compiling $<\\r"

$(NAME2)        : $(OBJS2)
	@printf "\033[K"
	@$(CC) $(CFLAGS) $^ -o $(NAME2) $(SDLFLAGS) -L libft -lft
	@printf "\033[37;1m-- $(NAME2)         [ \033[32;1mOK\033[37;1m ]\033[0m\\n"

# ****************************************************** Made by Zim-Zoom  *** #
