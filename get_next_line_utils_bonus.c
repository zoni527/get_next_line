/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:04:49 by jvarila           #+#    #+#             */
/*   Updated: 2024/11/27 16:36:49 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Function uses memmove to combine s1 and s2 and frees both pointers before
// returning the new combined string.
char	*strjoin_and_free(char *s1, char *s2)
{
	size_t	len1;
	size_t	combined_len;
	char	*str;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	combined_len = len1 + ft_strlen(s2);
	str = malloc((combined_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, len1);
	ft_memmove(str + len1, s2, combined_len - len1);
	str[combined_len] = '\0';
	free(s1);
	free(s2);
	return (str);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_char_ptr;
	const char	*src_char_ptr;
	size_t		i;

	if (n == 0)
		return (dest);
	dest_char_ptr = (char *)dest;
	src_char_ptr = (const char *)src;
	i = 0;
	if (src_char_ptr < dest_char_ptr)
		while (n-- > 0)
			dest_char_ptr[n] = src_char_ptr[n];
	else
	{
		while (i < n)
		{
			dest_char_ptr[i] = src_char_ptr[i];
			i++;
		}
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
