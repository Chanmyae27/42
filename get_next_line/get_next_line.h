/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:57:47 by cmyae             #+#    #+#             */
/*   Updated: 2026/10/25 18:16:18 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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

char	*get_next_line(int fd);
char	*ft_gnl(t_node *node, size_t len);
int		ft_find(t_node *lst);
int		ft_read_file(t_node **lst, t_node **last, int fd);
t_node	*ft_new_node(char *content, size_t len);
t_node	*ft_clean_buf(t_node *lst);
void	ft_add_back(t_node **lst, t_node **last, t_node *new);
void	*ft_free_lst(t_node **lst);
void	ft_shift_left(t_node *lst, size_t start);
size_t	ft_line_len(t_node *lst);

#endif
