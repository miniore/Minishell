/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:43:38 by porellan          #+#    #+#             */
/*   Updated: 2025/06/12 12:30:25 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_bzero(void *s, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_isalnum(char c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int n);
size_t	ft_strlcat(char*dest, const char *src, size_t s);
size_t	ft_strlen(const char *str);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t s);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t elem_count, size_t elem_size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int	ft_strcmp(char *s1, char *s2);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX FOPEN_MAX
# endif

char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *s, int n);
char	*ft_strjoin_gnl(char *s1, char const *s2);
char	*read_nl(char *temp, int fd);
char	*sub_nl(char *s);
char	*delete_nl(char *line_rd);

#endif
