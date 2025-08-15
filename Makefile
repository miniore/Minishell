# valgrind --leak-check=full --show-leak-kinds=all ./minishell
# valgrind --track-fds=yes --trace-children=yes
# -fsanitize=address -g3
NAME = minishell
LIBFT = Libft/libft.a

SRC_FILES = src/main.c \
			src/parse/syntax_parse.c \
			src/parse/redir_syntax_parse.c \
			src/parse/get_command.c \
			src/parse/tokenize.c \
			src/parse/exp_variables.c \
			src/parse/redir_tokenize.c \
			src/parse/parse_utils.c \
			src/parse/char_utils.c \
			src/free/free.c \
			src/free/final_free.c \
			src/error/error.c \
			src/env/env.c \
			src/env/env_tools.c \
			src/build_ins/pwd.c \
			src/build_ins/echo.c \
			src/build_ins/cd.c \
			src/build_ins/export.c \
			src/build_ins/unset.c \
			src/build_ins/exit.c \
			src/execution/executor.c \
			src/execution/exec_loop.c \
			src/execution/exec_commons.c \
			src/execution/exec_redir.c \
			src/signal/signal.c \
			src/redirection/redir_tools.c \
			src/execution/exec_redir_tools.c \
			src/execution/exec_loop_tools.c

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror
READ_FLAGS = -lreadline -lhistory
INCLUDE_FLAGS = -I Libft/ -I Libft/Printf/ -I include/
LINK_FLAGS = -L Libft -L Libft/Printf/ -lft -lftprintf

all: $(NAME)
		@echo "make    ✅"

$(NAME):$(LIBFT) $(OBJ_FILES) 
		$(CC) $(FLAGS) $(INCLUDE_FLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME) $(READ_FLAGS) $(LINK_FLAGS)
$(LIBFT):
		@$(MAKE) -sC Libft

%.o: %.c
		$(CC) $(FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
		@$(MAKE) clean -sC Libft
		@$(RM) $(OBJ_FILES)
		@echo "clean   🌪️"

fclean: clean
		@$(MAKE) fclean -sC Libft
		@$(RM) $(NAME)
		@echo "fclean  🔥"

re:		fclean all

.SILENT:

.PHONY: all clean fclean re