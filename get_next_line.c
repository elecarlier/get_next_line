/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:38:17 by ecarlier          #+#    #+#             */
/*   Updated: 2023/11/28 22:39:44 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	printf("#### leftover get_next_line before fill: %s \n", leftover);
	line = fill_line(fd, leftover);
	leftover = set_left(line);
	//printf("#### leftover get_next_line 2: %s \n", leftover);
	//free(leftover);
	return (line);
}

char	*fill_line(int fd, char *line)
{
	int		bytes_read;
	char	*buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1 ); //MALLOC 1
	if (!buffer)
	{
		free(buffer);
	}
	if (!line)
	{
		line = malloc(sizeof(char) * BUFFER_SIZE + 1); // MALLOC 2
		if (!line)
		{
			free(buffer);
			return (NULL);
		}
		line[0] = '\0'; // Assurez-vous que la chaîne est terminée par null
	}
	//line = malloc(sizeof(char) * BUFFER_SIZE + 1 ); //MALLOC
	printf("\n----line fill _line (before while) :%s\n", line);
	while (!ft_strchr(line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
		{
			free(line);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		//printf("\nBuffer inside :%s\n", buffer);
		line = ft_strjoin(line, buffer); //MALLOC 2 --- HAVE TO FREE
		printf("\n----line fill _line (after join) :%s\n", line);
	}

	free(buffer); //FREE 1
	return (line);

}

char	*set_left(char *line)
{
	char	*next;
	char	*leftover;

	//printf("\n ---- line set_left 1 :%s\n", line);
	next = ft_strchr(line, '\n');
	//printf("NEXT :%s\n", next);
	if (next == NULL)
		return (NULL);
	leftover = ft_strdup(next + 1); //MALLOC 3 --- HAVE TO FREE
	if (!leftover)
        return (NULL);
	*next = '\0';
	printf("\n####leftover set_left endfct : %s\n", leftover);
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
