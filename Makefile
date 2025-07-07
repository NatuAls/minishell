NAME = minishell

SRC = main.c
HDR = includes/minishell.h

CC = cc
RM = rm -rf
FLAGS = -Wall -Werror -Wextra -I .  

OBJ = $(SRC:.c=.o)
LIBFT = ./libft/libft.a

all: makelibft $(NAME)

%.o: %.c $(HDR) Makefile $(LIBFT)
			$(CC) $(FLAGS) -c $< -o $@

makelibft: 
	make -C ./libft

$(NAME): $(OBJ) $(libft)
			$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
clean: 
	 $(RM) $(OBJS)
	 make clean -C ./libft
fclean:
			$(RM) $(OBJS)
			$(RM) $(NAME)
			make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re libft

