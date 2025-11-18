# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 17:30:07 by peiyli            #+#    #+#              #
#    Updated: 2025/11/18 17:59:09 by yopeng           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

BONUS_SRC = ft_lstnew_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstsize_bonus.c \
ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c \
ft_lstclear_bonus.c \
ft_lstiter_bonus.c \
ft_lstmap_bonus.c \

SRC = ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_strlen.c \
ft_memset.c \
ft_bzero.c \
ft_memcpy.c \
ft_memmove.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_toupper.c \
ft_tolower.c \
ft_strchr.c \
ft_strrchr.c \
ft_strncmp.c \
ft_memchr.c \
ft_memcmp.c \
ft_strnstr.c \
ft_atoi.c \
ft_calloc.c \
ft_strdup.c \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_split.c \
ft_itoa.c \
ft_strmapi.c \
ft_striteri.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_printf.c \
ft_format.c \
ft_format_char.c \
ft_format_str.c \
ft_format_hexvoid.c \
ft_format_intd.c \
ft_format_unsignedint.c \
ft_format_hexlower.c \
ft_format_hexupper.c \
ft_format_percent.c \
ft_base2to16_lower.c \
ft_base2to16_lower_0x.c \
ft_base2to16_upper.c \
ft_putnbr.c \
ft_count_digit.c \
ft_putstr.c \
ft_putchar.c \
ft_strcpy.c \
get_next_line.c \
get_next_line_utils.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ =$(BONUS_SRC:.c=.o)
HEADER = libft.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
bonus: $(BONUS_OBJ)
	ar rcs $(NAME) $(BONUS_OBJ)
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
