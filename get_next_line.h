/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:37:22 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/20 16:09:04 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_buffer
{
	ssize_t			bytes_used;
	char			memory[BUFFER_SIZE];
	struct s_buffer	*next_buffer;
}	t_buffer;

typedef struct c_buffer_list
{
	int			fd;
	t_buffer	*first;
	t_buffer	*last;
}	t_buffer_list;

ssize_t	char_index(const char *buffer, char c);
size_t	ft_strlen(const char *str);
char	*flush_till_newline(t_buffer_list *buffer_list_pointer);
char	*get_next_line(int fd);
void	*free_buffer_list(t_buffer_list *buffer_list_pointer);
char	*extend_buffer(t_buffer_list *lst);

#endif
