/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:38:17 by ecarlier          #+#    #+#             */
/*   Updated: 2023/11/30 15:33:21 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	line = fill_line(fd, &leftover);
	leftover = set_left(line);

	if (line && !line)
	{
		free(line);
		free(leftover);
	}
	return (line);
}

char	*fill_line(int fd, char **line)
{
	int		bytes_read;
	char	buffer[BUFFER_SIZE +1];
	char	*temp;

	temp = NULL;
	if (!*line)
	{
		*line = malloc(sizeof(char) * 1); // Allocation initiale
		if (!*line)
			return (NULL);
		**line = '\0';
	}
	while (!ft_strchr(*line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
		{
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*line, buffer);
		if (!*line)
		{
   			free(*line);
   			return (NULL);
		}
		free(line);
		*line = temp;
	}
	return (*line);

}

char	*set_left(char *line)
{
	char	*next;
	char	*leftover;

	next = ft_strchr(line, '\n');
	if (!next)
		return (NULL);
	leftover = ft_strdup(next + 1);
	if (!leftover)
		return (NULL);
	return (leftover);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != '\0')
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
