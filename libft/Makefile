# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: israetor <israetor@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 19:49:49 by israetor          #+#    #+#              #
#    Updated: 2025/04/08 18:06:32 by israetor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRC_FILES	=	ft_bzero.c	ft_memset.c	ft_isalnum.c \
				ft_isalpha.c	ft_isascii.c	ft_isdigit.c \
				ft_isprint.c	ft_memcpy.c	ft_memmove.c \
				ft_memset.c	ft_strchr.c	ft_strlcat.c \
				ft_strlcpy.c	ft_strlen.c	ft_strncmp.c \
				ft_strrchr.c	ft_tolower.c	ft_toupper.c \
				ft_atoi.c	ft_isalnum.c ft_calloc.c \
				ft_isalpha.c	ft_isascii.c	ft_isdigit.c \
				ft_isprint.c	ft_memchr.c	ft_memcmp.c	\
				ft_memcpy.c	ft_memmove.c ft_strdup.c \
				ft_strchr.c	ft_strlcat.c	ft_strlcpy.c \
				ft_strlen.c	ft_strncmp.c	ft_strnstr.c \
				ft_strrchr.c	ft_tolower.c	ft_toupper.c \
				ft_substr.c	ft_strjoin.c	ft_strtrim.c \
				ft_itoa.c  ft_putchar_fd.c	ft_putstr_fd.c \
				ft_putendl_fd.c	ft_putnbr_fd.c ft_split.c \
				ft_striteri.c	ft_strmapi.c \
				get_next_line.c \
				ft_printf.c ft_printf_options.c ft_printhex.c\
				ft_putchar_print.c

BNS_FILES	=	ft_lstnew_bonus.c	ft_lstadd_front_bonus.c	ft_lstsize_bonus.c \
				ft_lstlast_bonus.c	ft_lstadd_back_bonus.c	ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c	ft_lstiter_bonus.c ft_lstmap_bonus.c

BNS_OBJ		=	$(BNS_FILES:.c=.o)

OBJ			=	$(SRC_FILES:.c=.o)

HDRS		=	libft.h

CC 			= gcc 
FLAGS 		= -Wall -Werror -Wextra  -I . 
		
%.o:		%.c $(HDRS) Makefile
			$(CC) $(FLAGS) -c $< -o $@

all:	    $(NAME)

$(NAME):	$(OBJ)
			ar -rcs $(NAME) $(OBJ)

bonus:		$(NAME) $(OBJ) $(BNS_OBJ)
			ar -rcs $(NAME) $(OBJ) $(BNS_OBJ)
			touch $@
clean:
			rm -f  $(OBJ) $(BNS_OBJ) 
fclean:		clean 
			rm -f $(NAME) bonus
re:			fclean all
	
.PHONY: clean all fclean re  
