#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static t_buffer buffer;
    char            *line = NULL;
    char            *temp = NULL;
    ssize_t         newline_index;

    if (fd < 0)
        return (NULL);
    // Initialize the buffer for the first call
    if (buffer.unflushed_bytes == 0 && buffer.flushed_bytes == 0)
    {
        buffer.fd = fd;
        read_into_buffer(&buffer);
    }

    while (1)
    {
        // Check if a newline exists in the buffer
        newline_index = get_newline_index(&buffer);
        if (newline_index >= 0)
        {
            // Extract up to and including the newline
            temp = flush(&buffer, newline_index + 1);
            if (!temp)
                return (free_ptr(line));
            line = strjoin_and_free(line, temp);
            return (line);
        }

        // If EOF is reached and no newline, flush remaining data
        if (buffer.eof && buffer.unflushed_bytes > 0)
        {
            temp = flush(&buffer, buffer.unflushed_bytes);
            if (!temp)
                return (free_ptr(line));
            line = strjoin_and_free(line, temp);
            return (line);
        }

        // If EOF is reached with no data, return NULL
        if (buffer.eof && buffer.unflushed_bytes == 0)
            return (line);

        // Flush whatever is available and read more data into the buffer
        temp = flush(&buffer, buffer.unflushed_bytes);
        if (temp)
            line = strjoin_and_free(line, temp);
        read_into_buffer(&buffer);
    }
}

