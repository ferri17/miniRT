<p align="center">
	<img alt="GitHub Repo stars" src="https://img.shields.io/github/stars/ferri17/libft?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/ferri17/libft" />
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/ferri17/libft?color=red" />
	<img alt="GitHub last commit (by committer)" src="https://img.shields.io/github/last-commit/ferri17/libft" />
	<img alt="MacOS compatibility" src="https://img.shields.io/badge/macOS-compatible-brightgreen.svg" />
</p>

<h3 align="center">Libft, personal static library (42 school project)</h3>

  <p align="center">
    The aim of this project is to create a static library to use during the cursus at 42 School.
    <br/>
  </p>
</div>

<!-- ABOUT THE PROJECT -->
## About The Project

Most of the **C standard library** functions are forbidden during 42 school curriculum, instead **students must create their own static library.**
Many of the functions that can be found in this library are **re-creations** of functions that already exist in libc, but some others are added 
beacuse they will be useful for future projects.

<!-- C standard library functions -->
## C standard library functions

- int		ft_isalpha(int c);
- int		ft_isdigit(int c);
- int		ft_isalnum(int c);
- int		ft_isascii(int c);
- int		ft_isprint(int c);
- size_t	ft_strlen(const char *s);
- void	*ft_memset(void *b, int c, size_t len);
- void	ft_bzero(void *s, size_t n);
- void	*ft_memcpy(void *dst, const void *src, size_t n);
- void	*ft_memmove(void *dst, const void *src, size_t len);
- size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
- size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
- int		ft_toupper(int c);
- int		ft_tolower(int c);
- char	*ft_strchr(const char *s, int c);
- char	*ft_strrchr(const char *s, int c);
- int		ft_strncmp(const char *s1, const char *s2, size_t n);
- void	*ft_memchr(const void *s, int c, size_t n);
- int		ft_memcmp(const void *s1, const void *s2, size_t n);
- char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
- int		ft_atoi(const char *str);
- void	*ft_calloc(size_t count, size_t size);
- char	*ft_strdup(const char *s1);
- int		ft_strcmp(const char *s1, const char *s2);

<!-- Extra functions libc -->
## Extra functions libc
This set of functions are either not in the libc, or are part of it in a different form:

- char	*ft_substr(char const *s, unsigned int start, size_t len);
- char	*ft_strjoin(char const *s1, char const *s2);
- char	*ft_strtrim(char const *s1, char const *set);
- char	**ft_split(char const *s, char c);
- char	*ft_itoa(int n);
- char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
- void	ft_striteri(char *s, void (*f)(unsigned int, char*));
- void	ft_putchar_fd(char c, int fd);
- void	ft_putstr_fd(char *s, int fd);
- void	ft_putendl_fd(char *s, int fd);
- void	ft_putnbr_fd(int n, int fd);

<!-- Lists manipulation functions -->
## Lists manipulation functions
This set of functions is used to manipulate lists:

- t_list	*ft_lstnew(void *content);
- void	ft_lstadd_front(t_list **lst, t_list *new);
- int		ft_lstsize(t_list *lst);
- t_list	*ft_lstlast(t_list *lst);
- void	ft_lstadd_back(t_list **lst, t_list *new);
- void	ft_lstdelone(t_list *lst, void (*del)(void *));
- void	ft_lstclear(t_list **lst, void (*del)(void *));
- void	ft_lstiter(t_list *lst, void (*f)(void *));
- t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

<!-- Special functions -->
## Special functions
To make the library more versatile a custom implementation of **printf(3)** was added. It was also useful to add a function 
to **extract text lines**, one at a time, from specific fd's.

- int		ft_printf(const char *str, ...);
- char	*get_next_line(int fd);

<!-- GETTING STARTED -->
## Getting Started
In order to get the library first clone the repository:
```bash
git clone git@github.com:ferri17/libft.git
```
Open the folder:
```bash
cd libft/
```
Compile the library:
```bash
make
```
You can now use `libft.a` library by linking it in your projects.
