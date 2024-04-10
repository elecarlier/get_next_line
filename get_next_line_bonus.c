/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:25:25 by ecarlier          #+#    #+#             */
/*   Updated: 2023/12/07 18:37:24 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*leftover[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	line = fill_line(fd, leftover[fd]);
	leftover[fd] = set_left(line);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*fill_line(int fd, char *line)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * BUFFER_SIZE +1);
	if (!buffer)
		free(buffer);
	while (!ft_strchr(line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*set_left(char *line)
{
	char	*next;
	char	*surplus;

	next = ft_strchr(line, '\n');
	if (next++ == NULL)
		return (NULL);
	surplus = ft_strdup(next);
	if (!surplus)
		return (NULL);
	*next = '\0';
	return (surplus);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	if (!s)
		return (NULL);
	ptr = (char *)s;
	while (*ptr != '\0')
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
