NAME = minishell
LIBFT = Libft/libft.a

SRC_FILES = src/main.c \
			src/get_command.c \
			src/tokenize.c \
			src/save_tokens.c \
			src/exp_variables.c \
			src/parse_utils.c \
			src/char_utils.c \
			src/free.c

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror
READ_FLAGS = -lreadline -lhistory

all: $(NAME)
		@echo "make    ✅"

$(NAME):$(OBJ_FILES) $(LIBFT)
		$(CC) $(FLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME) $(READ_FLAGS)

$(LIBFT):
		@$(MAKE) -C Libft

%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@

clean:
		$(MAKE) clean -C Libft
		$(RM) $(OBJ_FILES)
		@echo "clean   🌪️"

fclean: clean
		@$(MAKE) fclean -C Libft
		@$(RM) $(NAME)
		@echo "fclean  🔥"

re:		fclean all

.SILENT:

.PHONY: all clean fclean re