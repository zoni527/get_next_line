/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:47:36 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/20 11:51:23 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

	// Check whether the buffer contains a new line. If yes, 
	// return everything until and including that new line,
	// and move any remaining data back.

	// If no new line was found, attempt filling the buffer
	// and call function again.

	// If buffer is full either return NULL for error or create
	// extra buffers for extending the search area dynamically
	// and call get_next_line again

char	*get_next_line(int fd)
{
	static t_buffer_list	buffer_list;
	t_buffer				*buffer;
	t_buffer				*temp;
	ssize_t					new_line_index;

	buffer = buffer_list.last;
	if (!buffer->bytes_used)
		buffer->bytes_used = read(buffer_list.fd, buffer->memory, BUFFER_SIZE);
	if (buffer->bytes_used <= 0)
		return (free_buffer_list(&buffer_list));
	new_line_index = char_index(buffer->memory, '\n');
	if (new_line_index != -1)
		return (flush_till_newline(&buffer_list));
	if (buffer->bytes_used < BUFFER_SIZE)
	{
		buffer->bytes_used += read(fd, buffer->memory + buffer->bytes_used,
				BUFFER_SIZE - buffer->bytes_used);
		return (get_next_line(fd));
	}
	if (buffer->bytes_used == BUFFER_SIZE)
		return (extend_buffer(&buffer_list));
	return (NULL);
}

char	*flush_till_newline(t_buffer_list *buffer_list_pointer)
{
	size_t		line_len;
	t_buffer	*temp;
	char		*line;
	
	line_len = 0;
	temp = buffer_list_pointer->first->next_buffer;
	while (temp)
	{
		line_len += temp->bytes_used;
		temp = temp->next_buffer;
	}
	line = malloc((line_len + 1) * sizeof(char));
	if (!line)
	{
		free_buffer_list(buffer_list_pointer);
		return (NULL);
	}
	line[0] = '\0';
	temp = buffer_list_pointer->first;
	while (temp)
	{
		ft_strlcat(line, temp->memory, temp->bytes_used + 1);
		temp = temp->next_buffer;
	}
	return (line);
}
