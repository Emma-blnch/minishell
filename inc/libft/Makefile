# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 10:20:10 by mkling            #+#    #+#              #
#    Updated: 2025/03/10 09:17:04 by ahamini          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME	= libft.a


# Directories
SRC_DIR = src

OBJ_DIR = obj

INC_DIR = inc

# Flags
MAKEFLAGS += --no-print-directory
$(VERBOSE).SILENT:


# Files
SRCS 	= ft_atoi.c ft_bubble_sort.c ft_calloc.c ft_free_tab.c ft_isalnum.c \
		ft_isprint.c ft_itoa.c ft_lst_add.c ft_lst_iter.c ft_mem.c ft_minmax.c \
		ft_put.c ft_split.c ft_str_comps.c ft_str_dups.c ft_str_iteri.c \
		ft_strtrim.c ft_swap.c get_next_line.c ft_atoi_base.c ft_strnstr.c

OBJS	= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(addprefix $(SRC_DIR)/, $(SRCS)))


# Compilation options
CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g


# General rules
all:		$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
			ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				$(CC) $(CFLAGS) -g $(INC) -c $< -o $@

$(OBJ_DIR):
				mkdir -p $@

clean:
			rm -f $(OBJS)
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
