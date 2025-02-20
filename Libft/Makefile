NAME = libft.a
SRC_FILES = ft_atoi.c \
            ft_bzero.c \
            ft_calloc.c \
            ft_isalnum.c \
            ft_isalpha.c \
            ft_isascii.c \
            ft_isdigit.c \
            ft_isprint.c \
            ft_itoa.c \
            ft_memchr.c \
            ft_memcmp.c \
            ft_memcpy.c \
            ft_memmove.c \
            ft_memset.c \
            ft_putchar_fd.c \
            ft_putendl_fd.c \
            ft_putnbr_fd.c \
            ft_putstr_fd.c \
            ft_split.c \
            ft_strchr.c \
            ft_strdup.c \
            ft_striteri.c \
            ft_strjoin.c \
            ft_strlcat.c \
            ft_strlcpy.c \
            ft_strlen.c \
            ft_strmapi.c \
            ft_strncmp.c \
            ft_strrchr.c \
            ft_strtrim.c \
            ft_substr.c \
            ft_tolower.c \
            ft_toupper.c \
            ft_strnstr.c
SRC_FILES_BONUS = ft_lstadd_back_bonus.c \
					ft_lstadd_front_bonus.c \
					ft_lstclear_bonus.c \
					ft_lstdelone_bonus.c \
					ft_lstiter_bonus.c \
					ft_lstlast_bonus.c \
					ft_lstmap_bonus.c \
					ft_lstnew_bonus.c \
					ft_lstsize_bonus.c \
					get_next_line_bonus.c \
					get_next_line_utils_bonus.c
OBJ_FILES = $(SRC_FILES:.c=.o)
BONUS_OBJ_FILES = $(SRC_FILES_BONUS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = -rcs

all: $(NAME) bonus

$(NAME): $(OBJ_FILES)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_FILES)

$(OBJ_FILES): $(SRC_FILES)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(OBJ_FILES)
	rm -f $(BONUS_OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(BONUS_OBJ_FILES)
			$(AR) $(ARFLAGS) $(NAME) $(BONUS_OBJ_FILES)

.SILENT:

.PHONY: all name clean fclean re bonus