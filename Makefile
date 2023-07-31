# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 09:05:11 by moudrib           #+#    #+#              #
#    Updated: 2023/07/31 10:40:07 by moudrib          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3D
CC      = cc
CFLAGS	= -Wall -Wextra -Werror -g
OBJDIR	= _Object_files/
R		= \x1B[91m
G		= \x1B[32m
W		= \x1B[0m
B		= \033[1m
SRC		= \
			Parsing/cub3d.c \
			Parsing/parsing.c \
			Libft_utils/libft_utils1.c \
			Libft_utils/libft_utils2.c \
			Libft_utils/libft_utils3.c \
			Libft_utils/libft_utils4.c \
			Get_next_line/get_next_line.c \


			
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
# @clear
# @echo
# @echo "$(G)Cub3d compilation done ✔️"
# @echo
# @echo "                            $(R)██████$(W)╗ $(R)██$(W)╗   $(R)██$(W)╗ $(R)██████$(W)╗  $(R)██████$(W)╗  $(R)██████$(W)╗ "
# @echo "                           $(R)██$(W)╔════╝ $(R)██$(W)║   $(R)██$(W)║ $(R)██$(W)╔══$(R)██$(W)╗ ╚════$(R)██$(W)╗ $(R)██$(W)╔══$(R)██$(W)╗"
# @echo "                           $(W)█$(R)█$(W)║      $(W)█$(R)█$(W)║   $(R)█$(W)█$(W)║ $(W)█$(R)█████$(W)╔╝  $(R)█████$(W)╔╝ $(W)█$(R)█$(W)║  $(R)██$(W)║"
# @echo "                           $(W)██$(R)║      $(W)██$(R)║   $(W)██$(R)║ $(W)██$(R)╔══$(W)██$(R)╗  ╚═══$(W)██$(R)╗ $(W)██$(R)║  $(W)██$(R)║"
# @echo "                           ╚$(W)██████$(R)╗ ╚$(W)██████$(R)╔╝ $(W)██████$(R)╔╝ $(W)██████$(R)╔╝ $(W)██████$(R)╔╝"
# @echo "                            ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝ "
# @echo "                                                  $(B)$(R)Made by $(W)$(B)moudrib $(R)&& $(W)$(B)bbenidar"
# @echo
# @echo

$(OBJDIR)%.o: %.c cub3d.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(G)Compiling: $(W)$<"

clean:
	@rm -rf $(OBJDIR)

fclean:	clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
	
