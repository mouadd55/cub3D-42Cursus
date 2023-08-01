/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:03:57 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/01 12:42:53 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_infos
{
	int				*rgb;
	char			*value;
	char			*element;
	struct s_infos	*link;
}	t_infos;

typedef struct s_counter
{
	int				east;
	int				west;
	int				north;
	int				south;
	int				floor;
	int				ceiling;
}	t_counter;

typedef struct s_vars
{
	int				i;
	int				j;
	int				size;
	int				flag;
	int				length;
	int				map_fd;
	int				map_index;
	char			*str;
	char			**arr;
	char			**map;
	char			**elements;
	t_infos			*tmp;
}	t_vars;

/********************************* Libft utils ********************************/

void		ft_putnbr(int nbr);
void		ft_putstr(char *str);
ssize_t		ft_atoi(const char *str);
char		**ft_free_arr(char **arr);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strnstr(const char *str, const char *to_find, size_t len);

/******************************* Get next line ********************************/

char		*ft_save_rest(char *buf);
char		*ft_get_next_line(int fd);
int			ft_search_newline(char *s);
char		*ft_read_line(int fd, char *buf);

/***************************** Parsing functions ******************************/

int			ft_isdigit(char *str);
int			is_printable(char *line);
int			count_commas(char *value);
int			check_valid_extension(char *file_name);
void		ft_error(int cases, t_infos **infos, char **elements, char **arr);

int			check_rgb_values(t_infos *infos);
int			*create_rgb_arr(int r, int g, int b);
int			count_elements(t_vars *vars, t_counter *count);
void		check_if_informations_are_valid(char **elements);
int			check_missing_or_duplicated_element(t_infos **infos, t_vars vars);

t_infos		*ft_lstlast(t_infos *head);
void		*ft_destroy_list(t_infos **head);
t_infos		*ft_lstnew(char *element, char *value);
void		ft_lstadd_back(t_infos **head, t_infos *new);

#endif