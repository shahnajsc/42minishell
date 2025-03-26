/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:02:57 by shachowd          #+#    #+#             */
/*   Updated: 2025/03/26 08:59:45 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# if defined(__linux__)
#  define PTR_NULL "(nil)"
# elif defined(__APPLE__)
#  define PTR_NULL "0x0"
# else
#  define PTR_NULL "Unknown"
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//LIBFT
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					check_white_spaces(char *str);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *str, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
int					ft_strcmp(char *s1, char *s2);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(char *s1, char *s2, unsigned int n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
long				ft_atoi(char const *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *src);

char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start,
						size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s,
						char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_grid_rows(char **grid);
void				ft_free_grid(void **grid);
char				**ft_grid_dup(char **grid);

//PRINTF
int					ft_print_char(int fd, char c);
int					ft_print_percent(int fd);
int					ft_print_str(int fd, char *str);
int					ft_print_nbr(int fd, int n);
int					ft_print_unsign(int fd, unsigned int nbr);
int					ft_print_ptr(int fd, unsigned long ptr);
char				*ft_strchr_pf(const char *s, int c);
int					ft_print_hex(int fd, unsigned long n, char *strhex);
int					ft_printf(int fd, const char *str, ...);

//GNL
size_t				ft_len_line(char *str);
char				*get_next_line(int fd);

//READER
char				*ft_line_reader(int fd, char *line, int buffer, int index);

#endif
