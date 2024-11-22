/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:47:36 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/21 13:03:49 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>

// Check whether the buffer contains a new line. If yes, 
// return everything until and including that new line,
// and move any remaining data back.

// If no new line was found, attempt filling the buffer
// and call function again.

// If the buffer is full, create a mallocated string to
// hold it, store the return value of a new recursive
// call to get_next_line, concatenate them, free extra
// space and return the complete line.

// If no new line is found return whatever is found
// when encountering EOF

static char	*flush_till_index(t_buffer *buffer, size_t index);
static void	read_into_buffer(t_buffer *buffer);
static char	*store_buffer_and_append_next_line(t_buffer *buffer);
static void	move_buffer_back(t_buffer *buffer, size_t offset);

char	*get_next_line(int fd)
{
	if (fd < 0)
		return (NULL);
	static t_buffer	buffer;
	ssize_t			newline_index;

	if (!buffer.fd)
		buffer.fd = fd;
	newline_index = char_index(&buffer, '\n');
	if (newline_index != -1)
		return (flush_till_index(&buffer, newline_index + 1));
	if (buffer.eof)
		return (flush_till_index(&buffer, buffer.bytes_used));
	if (buffer.bytes_used < BUFFER_SIZE)
	{
		read_into_buffer(&buffer);
		return (get_next_line(fd));
	}
	if (buffer.bytes_used == BUFFER_SIZE)
		return (store_buffer_and_append_next_line(&buffer));
	return (NULL);
}

static char	*store_buffer_and_append_next_line(t_buffer *buffer)
{
	char	*storage;
	char	*next_line;

	storage = flush_till_index(buffer, buffer->bytes_used);
	if (!storage)
		return (NULL);
	next_line = get_next_line(buffer->fd);
	if (!next_line)
		return (free_ptr(storage));
	return (strjoin_and_free(storage, next_line));
}

static void	read_into_buffer(t_buffer *buffer)
{
	ssize_t	bytes_read;

	bytes_read = read(
			buffer->fd,
			buffer->memory + buffer->bytes_used,
			BUFFER_SIZE - buffer->bytes_used);
	buffer->bytes_used += bytes_read;
	if (buffer->bytes_used != BUFFER_SIZE)
		buffer->eof = 1;
}

static void	move_buffer_back(t_buffer *buffer, size_t offset)
{
	size_t		bytes_to_move;
	const char	*offset_start_position;

	bytes_to_move = buffer->bytes_used - offset;
	offset_start_position = buffer->memory + offset;
	if (offset == 0)
		return ;
	ft_memmove(buffer->memory, offset_start_position, bytes_to_move);
	buffer->bytes_used -= offset;
}

static char	*flush_till_index(t_buffer *buffer, size_t index)
{
	char	*next_line;

	if (!buffer->bytes_used || index == 0)
		return (NULL);
	next_line = malloc((index + 1) * sizeof(char));
	if (!next_line)
		return (NULL);
	ft_memmove(next_line, buffer->memory + buffer->offset, index);
	next_line[index] = '\0';
	move_buffer_back(buffer, index);
	return (next_line);
}
