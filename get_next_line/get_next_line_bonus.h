/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:57:47 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/24 17:57:20 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_node
{
	char			*content;
	size_t			len;
	struct s_node	*next;
}	t_node;

typedef struct s_fd_node
{
	int						fd;
	t_node					*node;
	t_node					*last;
	struct s_fd_node		*next;
}	t_fd_node;

char		*get_next_line(int fd);
char		*ft_gnl(t_node *node);
int			ft_find(t_node *lst);
int			ft_read_file(t_fd_node **lst, int fd);
size_t		ft_line_len(t_node *node);
t_fd_node	*ft_set_fd(t_fd_node **lst, int fd);
t_node		*ft_create(char *content, size_t len, t_fd_node **lst);
void		ft_remove_fd(t_fd_node **lst, int fd);
void		ft_clean_stash(t_fd_node **lst);
void		ft_shift_left(t_node *node, size_t start);

#endif
