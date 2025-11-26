MAKEFLAGS += --silent

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -Ilibft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = \
	src/main.c \
	src/parse/quote.c \
	src/parse/parseline.c \
	src/parse/dollar_env.c \
	src/parse/dollar_replace.c \
	src/parse/create_list_cmd.c \
	src/parse/create_list_token.c \
	src/parse/list_token_utils.c \
	src/parse/cmd_param.c \
	src/parse/cmd_fd.c \
	src/utils/free.c \
	src/utils/utils.c \
	src/utils/utils_list.c \
	src/utils/utils_array.c \
	src/utils/signal.c \
	src/utils/debug.c \
	src/utils/replace.c \
	src/utils/export_utils.c \
	src/utils/quote_utils.c \
	src/exec/here_doc.c \
	src/exec/builtin.c \
	src/exec/exec.c \
	src/exec/exec2.c \
	src/exec/absolute_path.c \
	src/exec/cmd_exist.c \
	src/builtin/ft_echo.c \
	src/builtin/ft_env.c \
	src/builtin/ft_export.c \
	src/builtin/ft_cd.c \
	src/builtin/ft_cd2.c \
	src/builtin/ft_pwd.c \
	src/builtin/ft_exit.c \
	src/builtin/ft_unset.c

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@printf "\033[0;32m✅ Minishell compiled successfully!\033[0m\n"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c
	mkdir -p $(OBJ_DIR)/parse $(OBJ_DIR)/utils $(OBJ_DIR)/exec $(OBJ_DIR)/builtin
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re