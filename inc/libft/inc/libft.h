/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:19:31 by skassimi          #+#    #+#             */
/*   Updated: 2025/03/10 09:16:44 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_list
{
	int				type;
	char			*str;
	char			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *ptr, int value, size_t count);
void	*ft_memcpy(void *dest, const void *src, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_bzero(void *ptr, unsigned long len);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, int size);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new, int type);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
char	*ft_strjoinfree(char *s1, char const *s2);
char	*get_next_line(int fd);
void	ft_free_tab(char **array);
long	ft_atol(const char *str);
size_t	countword(const char *str, char sep);
int		ft_min(int num1, int num2);
int		ft_max(int num1, int num2);
void	ft_bubble_sort(int	*num_array, int size_array);
void	ft_swap_int(int *a, int *b);
int		is_too_long_for_int(char *str);
int		ft_abs(int num);
int		ft_isdigit_or_hexa(int c);
void	ft_free_matrix(int	**matrix);
int		ft_atoi_base(char *str, char *base);
void	ft_lstpop(t_list **head, t_list *node, void (*del)(void *));
int		ft_iseven(int num);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);


#endif