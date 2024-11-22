/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:37:22 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/21 13:07:30 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_buffer
{
	int			fd;
	int			eof;
	size_t		flushed_bytes;
	size_t		unflushed_bytes;
	char		memory[BUFFER_SIZE + 1];
}	t_buffer;

ssize_t	char_index(t_buffer *buffer, char c);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*free_ptr(void *ptr);
char	*strjoin_and_free(char *s1, char *s2);

#endif
