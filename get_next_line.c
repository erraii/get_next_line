/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:12 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/14 03:25:45 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	t_getline	s_line;
	static char	*buffer_remain;

	s_line.linelen = 0;
	s_line.newlinefound = 0;
	s_line.line = 0;
	s_line.tmp_str = 0;

	// if (buffer_remain && *buffer_remain)
	// {
	// 	s_line.until_nl = until_nl(buffer_remain, &s_line.until_nl_len);
	// 	//printf("buffer_remain: %s\n", buffer_remain);
	// 	//printf("line.until_nl: %s\n", s_line.until_nl);
	// 	//printf("line.until_nl_len: %ld\n", s_line.until_nl_len);
	// 	if (s_line.until_nl)
	// 	{
	// 		s_line.after_nl_len = ft_strlen(buffer_remain) - s_line.until_nl_len;
	// 		s_line.line = ft_strdup(s_line.until_nl);
	// 		free(s_line.until_nl);
	// 		if (s_line.after_nl_len > 0)
	// 		{
	// 			s_line.tmp_str = ft_substr(buffer_remain, s_line.until_nl_len, s_line.after_nl_len);
	// 			free(buffer_remain);
	// 			buffer_remain = ft_strdup(s_line.tmp_str);
	// 			free(s_line.tmp_str);
	// 		}
	// 		else
	// 			free(buffer_remain);
	// 		return (s_line.line);
	// 	}
	// 	s_line.until_nl_len = 0;
	// }

	while (s_line.newlinefound == 0)
	{
		s_line.buffer = malloc(BUFFER_SIZE + 1);
		if (!s_line.buffer)
			return (0);
		s_line.bytesread = read(fd, s_line.buffer, BUFFER_SIZE);
		//printf("bytesread: %ld\n", s_line.bytesread);
		if (s_line.bytesread > 0)
		{
			s_line.buffer[s_line.bytesread] = '\0';
			//printf("buffer: %s\n", s_line.buffer);
			s_line.until_nl = until_nl(s_line.buffer, &s_line.until_nl_len);
			//printf("until nl: %s\n", s_line.until_nl);
			s_line.after_nl_len = s_line.bytesread - s_line.until_nl_len;
			//printf("until_nl_len: %ld\n", s_line.until_nl_len);
			//printf("after_nl_len: %ld\n", s_line.after_nl_len);
			if (s_line.until_nl_len > 0)
			{
				s_line.newlinefound = 1;
				s_line.linelen += s_line.until_nl_len;
			}
		}
		if (buffer_remain && *buffer_remain)
			s_line.linelen += ft_strlen(buffer_remain);
		//printf("reached here\n");
		if (s_line.linelen > 0)
		{
			if (s_line.line)
			{
				//printf("s.line exists\n");
				s_line.tmp_str = ft_strdup(s_line.line);
				free (s_line.line);
			}
			//printf("reached here 2\n");
			s_line.line = malloc(s_line.linelen + 1);
			if (s_line.tmp_str)
			{
				//printf("s.tmp_line exists\n");
				ft_strlcat(s_line.line, s_line.tmp_str, s_line.linelen + 1);
				free(s_line.tmp_str);
			}
			if (buffer_remain && *buffer_remain)
			{
				//printf("buffer_remain: %s\n", buffer_remain);
				ft_strlcpy(s_line.line, buffer_remain, ft_strlen(buffer_remain) + 1);
				free(buffer_remain);
			}
			if (s_line.until_nl)
			{
				//printf("reached here 3\n");
				//printf("linelen: %ld\n", s_line.linelen);
				ft_strlcat(s_line.line, s_line.until_nl, s_line.linelen + 1);
				free (s_line.until_nl);
				//printf("line: %s\n", s_line.line);
			}
		}
		if (s_line.after_nl_len > 0)
		{
			buffer_remain = ft_substr(s_line.buffer, s_line.until_nl_len, s_line.after_nl_len);
			//printf("buffer_remain: %s\n", buffer_remain);
		}
		free(s_line.buffer);
	}
	return (s_line.line);
}


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

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	for (int i = 0; i < 43; i++)
	{
		line = get_next_line(fd);
		printf("line[%d]: %s", i + 1, line);
		free (line);
	}
	close(fd);
}
