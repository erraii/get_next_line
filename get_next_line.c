/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:12 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/13 00:53:08 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*remain;
	size_t		bytesread;
	size_t		newlineloc;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	bytesread = read(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE] = '\0';
	printf("buffer: %s", buffer);
	newlineloc = ft_strchrloc(buffer, '\n', BUFFER_SIZE);
	line = malloc(newlineloc + 1 + strlen(remain));
	if (!line)
		return (0);
	ft_strlcpy(line, buffer, newlineloc + 1);
	printf("line: %s", line);
	if (!remain)
	{
		remain = malloc(BUFFER_SIZE);
		if (!remain)
			return (0);
	}
	ft_strlcpy(remain, buffer + newlineloc, BUFFER_SIZE - newlineloc + 1);
	printf("remain: %s", remain);
	free (buffer);
	return (line);

	// size_t		bytesread;
	// static char	*buffer;
	// static int	bufferloc;
	// static char	*line;
	// int			len;

	// if (bufferloc > 0)
	// {
	// 	len = ft_strchrl(buffer, bufferloc, '\n');
	// 	if (len > 0)
	// 	{
	// 		line = ft_substr(buffer, bufferloc, len);
	// 		bufferloc += len;
	// 	}
	// 	else
	// 	{
	// 		line = ft_substr(buffer, bufferloc, BUFFER_SIZE - bufferloc);
	// 		bufferloc = 0;
	// 	}
	// }
	// while (bufferloc == 0)
	// {
	// 	buffer = malloc(BUFFER_SIZE);
	// 	bytesread = read(fd, buffer, BUFFER_SIZE);
	// 	if (bytesread > 0)
	// 	{
	// 		if (bytesread < BUFFER_SIZE)
	// 			bufferloc = bytesread;
	// 		else
	// 			bufferloc = ft_strchrl(buffer, 0, '\n');
	// 		if (bufferloc > 0)
	// 		{
	// 			if (line == NULL)
	// 				line = ft_substr(buffer, 0, bufferloc);
	// 			else
	// 				line = ft_strjoin(line, ft_substr(buffer, 0, bufferloc));
	// 		}
	// 		else if (line == NULL)
	// 			line = ft_substr(buffer, 0, BUFFER_SIZE);
	// 		else
	// 			line = ft_strjoin(line, ft_substr(buffer, 0, BUFFER_SIZE));
	// 	}
	// 	else
	// 		return (NULL);
	// }
	// return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	//printf("%s", line);
	free (line);
	line = get_next_line(fd);
	//printf("%s", line);
	free (line);
	close(fd);
}
