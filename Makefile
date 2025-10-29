#用于隐藏隐冗长的中间输出
#MAKEFLAGS += --silent

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

#随着c文件的增加，加c文件名称#
SRC = \
	src/main.c \
	src/parse/quote.c \
	src/parse/parseline.c \
	src/parse/dollar_env.c \
	src/parse/dollar_replace.c \
	src/parse/create_list_cmd.c \
	src/parse/create_list_token.c \
	src/parse/cmd_param.c \
	src/utils/free.c \
	src/utils/utils.c \
	src/utils/utils_list.c

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@printf "\033[0;32m✅ Minishell compiled successfully!\033[0m\n"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

#随着文件夹的增加，要在$(obj_dir)后面加文件夹名称#
$(OBJ_DIR)/%.o: src/%.c
	mkdir -p $(OBJ_DIR)/parse $(OBJ_DIR)/utils
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re