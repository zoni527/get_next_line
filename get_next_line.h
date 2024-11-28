/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:37:22 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/25 14:05:03 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef FILE_LIMIT
#  define FILE_LIMIT 10
# endif

typedef struct s_buffer
{
	int			fd;
	int			eof;
	size_t		flushed_bytes;
	size_t		unflushed_bytes;
	char		memory[BUFFER_SIZE];
}	t_buffer;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*strjoin_and_free(char *s1, char *s2);

#endif
