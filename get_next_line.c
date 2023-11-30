/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:38:17 by ecarlier          #+#    #+#             */
/*   Updated: 2023/11/30 21:27:53 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	line = fill_line(fd, leftover);
	leftover = set_left(line);
	if (line == NULL)
		return (NULL);
	//printf("return value line : %s \n", line);
	return (line);
}

char	*fill_line(int fd, char *line)
{
	int		bytes_read;
	char	buffer[BUFFER_SIZE +1];

	if (!line)
	{
		line = malloc(sizeof(char) * BUFFER_SIZE);
		if (!line)
			return (NULL);
		*line = '\0';
	}
	while (!ft_strchr(line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			line = NULL;
			break ;
		}
		if (bytes_read == -1)
		{
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
	}
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
