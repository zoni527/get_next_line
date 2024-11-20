/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:04:49 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/20 21:02:17 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	char_index(const char *buffer, char c)
{
	ssize_t	i;

	i = -1;
	while (buffer[++i])
		if (buffer[i] == c)
			return (i);
	if (c == '\0')
		return (i);
	return (-1);
}

void	*free_buffer_list(t_buffer_list *lst_ptr)
{
	t_buffer	*temp;
	t_buffer	*to_free;
	size_t		i;

	if (lst_ptr->first == lst_ptr->last)
	{
		i = 0;
		while (i < BUFFER_SIZE)
			lst_ptr->first->memory[i++] = '\0';
		return (NULL);
	}
	temp = lst_ptr->first->next_buffer;
	while (temp)
	{
		to_free = temp;
		temp = temp->next_buffer;
		free(to_free);
	}
	return (NULL);
}

char	*extend_buffer(t_buffer_list *lst)
{
	t_buffer	*temp;

	lst->last = malloc(sizeof(t_buffer));
	if (!lst->last)
		return (free_buffer_list(lst));
	temp = lst->first;
	while (temp->next_buffer)
		temp = temp->next_buffer;
	temp->next_buffer = lst->last;
	return (get_next_line(lst->fd));
}
