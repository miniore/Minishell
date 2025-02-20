NAME = libftprintf.a
SRC_FILES = ft_printf.c \
			ft_printf_utils.c \
			ft_printf_utils_2.c
OBJ_FILES = $(SRC_FILES:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = -rcs

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_FILES)

$(OBJ_FILES): $(SRC_FILES)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SILENT:

.PHONY: all name clean fclean re