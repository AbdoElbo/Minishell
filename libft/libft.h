/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:20:16 by hariskon          #+#    #+#             */
/*   Updated: 2025/08/12 15:57:58 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int a);
int		ft_isdigit(int a);
int		ft_isalnum(int a);
int		ft_isascii(int a);
int		ft_isprint(int a);
int		ft_toupper(int a);
int		ft_tolower(int a);
int		ft_strlen(const char *array);

char	*ft_strchr(char *letter, int a);
char	*ft_strnstr(const char *haystack, const char *needle, size_t size);
char	*ft_strrchr(char *letter, int a);
int		ft_strncmp(const char *s1, const char *s2, size_t size);

void	*ft_memset(void *array, int value, size_t size);
void	*ft_memchr(const void *array, int value, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t size);
int		ft_memcmp(const void *array1, const void *array2, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t size);
void	ft_bzero(void *array, size_t size);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);

long	ft_atoi(const char *array);

void	*ft_calloc(size_t num_elements, size_t elements_size);
char	*ft_strdup(const char *src);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lsr, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char	*get_next_line(int fd);
char	*read_until_break(char *saved, int fd);
char	*split_line(char *saved);
char	*get_leftover(char *saved);
char	*gnl_strjoin_free(char *s1, char *s2);

int		ft_printf(const char *format, ...);
int		character(char c);
int		string(char *str);
int		sign_num(int d);
int		type_check(va_list args, char c);
int		unsign_num(unsigned int n);
int		hex_lower(unsigned int n);
int		hex_upper(unsigned int n);
int		pointer(void *p);
void	write_char(char c, int fd);

#endif
