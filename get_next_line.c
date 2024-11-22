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

static char	*flush(t_buffer *buffer, size_t bytes_to_flush);
static void	read_into_buffer(t_buffer *buffer);
static void	initialize(t_buffer *buffer, int fd);

static ssize_t	get_newline_index(t_buffer *buffer)
{
	size_t	offset;
	size_t	i;

	offset = buffer->flushed_bytes;
	i = 0;
	while (i < buffer->unflushed_bytes)
	{
		if (buffer->memory[offset + i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	char			*next_line;
	char			*storage;
	ssize_t			newline_index;

	if (fd < 0)
		return (NULL);
	if (buffer.unflushed_bytes == 0 && buffer.flushed_bytes == 0)
		initialize(&buffer, fd);
	newline_index = get_newline_index(&buffer);
	if (newline_index >= 0)
		return (flush(&buffer, newline_index + 1));
	if (buffer.eof && newline_index == -1)
		return (flush(&buffer, buffer.unflushed_bytes));
	storage = flush(&buffer, buffer.unflushed_bytes);
	if (!storage)
		return (NULL);
	read_into_buffer(&buffer);
	next_line = get_next_line(fd);
	if (!next_line)
		return (free_ptr(storage));
	next_line = strjoin_and_free(storage, next_line);
	return (next_line);
}

static void	read_into_buffer(t_buffer *buffer)
{
	ssize_t	bytes_read;

	bytes_read = read(buffer->fd, buffer->memory, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		buffer->eof = 1;
		return ;
	}
	buffer->unflushed_bytes = bytes_read;
	buffer->flushed_bytes = 0;
	if (bytes_read < BUFFER_SIZE)
		buffer->eof = 1;
}

static char	*flush(t_buffer *buffer, size_t bytes_to_flush)
{
	char	*line;
	size_t	offset;
	size_t	i;

	if (buffer->unflushed_bytes == 0 || bytes_to_flush == 0)
		return (NULL);
	if (bytes_to_flush > buffer->unflushed_bytes)
		bytes_to_flush = buffer->unflushed_bytes;
	line = malloc((bytes_to_flush + 1) * sizeof(char));
	if (!line)
		return (NULL);
	offset = buffer->flushed_bytes;
	i = 0;
	while (i < bytes_to_flush)
	{
		line[i] = buffer->memory[offset + i];
		i++;
	}
	line[i] = '\0';
	buffer->unflushed_bytes -= bytes_to_flush;
	buffer->flushed_bytes += bytes_to_flush;
	return (line);
}

static void	initialize(t_buffer *buffer, int fd)
{
	buffer->fd = fd;
	read_into_buffer(buffer);
}
