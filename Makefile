# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 15:54:29 by ahamini           #+#    #+#              #
#    Updated: 2025/03/03 13:06:29 by ahamini          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#		General variables													   #
# **************************************************************************** #

NAME		= minishell

MAKEFLAGS += --no-print-directory

DIR_SRC		= src
DIR_EXEC	= execution
DIR_PARS	= parsing
DIR_BUTI	= builtins

DIR_OBJ		= obj
DIR_OBJS	= $(DIR_OBJ) $(DIR_OBJ)/$(DIR_EXEC) $(DIR_OBJ)/$(DIR_PARS) $(DIR_OBJ)/$(DIR_BUTI)

DIR_INC		= inc

DIR_LIB		= $(DIR_INC)/libft

HEADER		= $(DIR_INC)/minishell.h

MAIN		=	main.c

FUNC_EXEC	= 	execution.c \
				exec2.c \
				exec_utils.c \
				find_cmd.c \
				setup.c \
				heredoc.c

				
FUNC_PARS	=	cleanup.c \
				cleanup2.c \
				cmd_fd.c \
				cmd_utils.c \
				dollar_utils.c \
				dollar_utils2.c \
				errors.c \
				manage_dollar.c \
				parse_cmd.c \
				quote.c \
				readline.c \
				signals.c \
				signals2.c \
				token_utils.c \
				token.c

FUNC_BUTI	=	cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				export_utils.c \
				pwd.c \
				unset.c \
				builtins.c

FUNC		= 	$(addprefix $(DIR_EXEC)/, $(FUNC_EXEC)) \
				$(addprefix $(DIR_PARS)/, $(FUNC_PARS)) \
				$(addprefix $(DIR_BUTI)/, $(FUNC_BUTI)) \

MAIN		= main.c

SRC			= 	$(addprefix $(DIR_SRC)/, $(FUNC)) \
				$(addprefix $(DIR_SRC)/, $(MAIN))

OBJ			= $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

LIB			= $(DIR_LIB)/libft.a

DEP			= $(LIB) $(DIR_OBJS) $(HEADER)

INC			= -I$(DIR_INC) -I$(DIR_LIB)

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g3

# **************************************************************************** #
#		Unit test variables													   #
# **************************************************************************** #

T_NAME		= utest

T_DIR		= test

T_SRC		= utest.c

T_OBJ		= utest.o

T_INC		= -I$(HOME)/Criterion/include/ \
				-I$(HOME)/Criterion/ \
				$(INC)

T_LIB		= -Wl,-rpath=$(HOME)/Criterion/build/src \
				-L$(HOME)/Criterion/build/src \
				-L$(HOME)/Criterion \
				-lcriterion \
				-L$(DIR_LIB) -lft -lreadline

T_CC		= $(CC) $(CFLAGS) $(T_INC) -g

T_EXCL		= obj/main.o

V_FLAG		= valgrind --leak-check=full --show-leak-kinds=all \
				--track-origins=yes --trace-children=yes --track-fds=yes \
				--suppressions=inc/readline.supp

# **************************************************************************** #
#																			   #
#			COMPILATION														   #
#																			   #
# **************************************************************************** #

all:				$(NAME)

$(NAME):			$(DEP) $(OBJ)
					$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ) -L$(DIR_LIB) \
					-lft -lreadline

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c
					$(CC) $(CFLAGS) $(INC) -c $< -o  $@

$(DIR_OBJS):
					mkdir -p $@

$(LIB):
					make -C $(DIR_LIB)


# **************************************************************************** #
#																			   #
#			TEST AND DEBUG													   #
#																			   #
# **************************************************************************** #

debug:		$(DEP) $(OBJ)
			@echo "Compiling with debug flag"
			$(CC) $(CFLAGS) -g $(INC) -o $(NAME) $(SRC) -L$(DIR_LIB) \
			-lft -lreadline

$(T_NAME):	$(DEP) $(OBJ)
			@echo "Compiling unit test"
			$(T_CC) $(LIB) $(T_LIB) $(filter-out $(T_EXCL), $(OBJ)) \
			$(addprefix $(T_DIR)/, $(T_SRC)) -o $(T_DIR)/$(T_NAME) -L$(DIR_LIB) \
			-lft -lreadline

test:		$(T_NAME)
			@echo "Running unit tests :"
			./$(T_DIR)/$(T_NAME)

valgrind:	$(NAME)
			@echo "Running with valgrind :"
			$(V_FLAG) ./$(NAME)

# **************************************************************************** #
#																			   #
#			CLEAN UP														   #
#																			   #
# **************************************************************************** #

clean:
			rm -rf $(DIR_OBJ)
			rm -rf $(T_DIR)/$(T_NAME)
			make -C $(DIR_LIB) clean

fclean:
			rm -rf $(DIR_OBJ)
			rm -rf $(T_DIR)/$(T_NAME)
			rm -rf $(NAME)
			make -C $(DIR_LIB) fclean

re:			fclean all

.PHONY:		all clean fclean re debug test compile
