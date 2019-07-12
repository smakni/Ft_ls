# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabri <sabri@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 13:20:28 by smakni            #+#    #+#              #
#    Updated: 2019/07/12 13:08:47 by sabri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls

CC			=	gcc

CFLAGS		+=	-Wall -Werror -Wextra -g3

CPPFLAGS	=	-I includes -I libft/includes

HEADER		=	./includes/ft_ls.h
				
SRC_PATH	=	src

OBJ_PATH	=	obj

LDFLAGS		=	-L libft

LDLIBS		=	-lft

SRC_NAME	=	main.c\
				option.c\
				ft_realloc_tab.c

OBJ_NAME	=	$(SRC_NAME:.c=.o)

SRC 		= 	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ 		= 	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		make -C libft
		$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

sanitize: 
		make -C libft
		$(CC) -fsanitize=address -g3  -o fl_ls $(OBJ) $(LDFLAGS) $(LDLIBS)

resanitize: fclean $(OBJ) 
		make -C libft
		$(CC) -fsanitize=address -g3  -o ft_ls $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm -fv $(OBJ)
	rmdir $(OBJ_PATH) 2> /dev/null || true
	make clean -C libft

fclean: clean
	rm -fv $(NAME)
	make fclean -C libft

re:
	make fclean
	make

.PHONY: all, clean, fclean, re

norme_src:
	norminette src/*.[ch]
	norminette ./includes

norme_lib:
	norminette ./libft/*/*.[ch]
	norminette ./libft/includes
