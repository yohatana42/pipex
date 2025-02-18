# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/08 14:55:25 by yohatana          #+#    #+#              #
#    Updated: 2025/02/17 19:12:02 by yohatana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name
NAME		= pipex

# src files
SRCS		=\
				main.c\
				validate_args.c\
				get_env_path.c\
				exec.c\
				create_struct.c\
				data_set_to_struct.c


# object file name
OBJS		= $(SRCS:.c=.o)

# compile flag
CC			= cc
CCFLAGS		= -Wall -Wextra -Werror
# CCFLAGS		+= -fsanitize=address

# Archive and remove command
AR			= ar rcs
RM			= rm -f

.DEFAULT:	all

all:		$(NAME)

# libft
LIBFT = libft
$(LIBFT)/libft.a:
		make -C $(LIBFT)

# printf
PRINTF = printf
$(PRINTF)/libftprintf.a:
		make -C $(PRINTF)

%.o: %.c
		$(CC) $(CCFLAGS) -I$(LIBFT) -I$(PRINTF) -c $< -o $@

${NAME}:	${OBJS} $(PRINTF)/libftprintf.a $(LIBFT)/libft.a
			$(CC) $(CCFLAGS) ${OBJS} -L$(LIBFT) -lft -L$(PRINTF) -lftprintf -o $(NAME)

clean:
			make -C $(PRINTF) clean
			make -C $(LIBFT) clean
			${RM} $(OBJS)

fclean:		clean
			make -C $(LIBFT) fclean
			make -C $(PRINTF) fclean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
