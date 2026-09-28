NAME	= minishell
CFLAGS	= -Wextra -Wall -Werror -g
CC		= gcc
LIBS	= -lreadline
LIBFT_DIR	= ./lib/libft
LIBFT_PATH	= ./lib/libft/libft.a
LIBS_PATH	= $(LIBFT_PATH) $(LIBS)


SRCS	= ./src/minishell.c \
			./src/builtins_utils.c \
			./src/builtin_echo.c \
			./src/builtins_export.c \
			./src/builtins_unset.c \
			./src/builtins_exit_pwd.c \
			./src/signals.c \
			./src/ft_split_up.c \
			./src/utils.c \
			./src/lexer.c \
			./src/open_files.c \
			./src/join_cmd_built.c \
			./src/handle_redirections.c \
			./src/convert_cmd.c \
			./src/choose_fork.c \
			./src/fork_execution.c \
			./src/set_up_heredoc.c \
			./src/set_up_pipe.c \
			./src/free.c \
			./src/expander.c \
			./src/expander_utils.c \
			./src/choose_fork_utils.c \
			./src/builtin_cd_env.c \
			./src/reset.c \
			./src/main.c \
			./src/expander_str.c
			

OBJ_DIR	= ./obj
OBJS	= ${SRCS:./src/%.c=$(OBJ_DIR)/%.o}

GREEN = \033[1;32m

all : $(NAME)

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(OBJS) $(LIBS_PATH) -o $(NAME)
	@echo "${GREEN}Minishell compiled"

clean:
	@rm -rf $(OBJ_DIR)
	@make -s clean -C $(LIBFT_DIR)
	@echo "${GREEN}clean completed"

fclean: clean
	@rm -rf $(NAME)
	@make -s fclean -C $(LIBFT_DIR)
	@echo "${GREEN}fclean completed"

re: fclean all

.PHONY: all, clean, fclean, re