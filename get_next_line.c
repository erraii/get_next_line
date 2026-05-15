/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:12 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/15 15:54:52 by ecakiray         ###   ########.fr       */
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
	static char	*left_over;

	s_line.line = 0;
	s_line.buffer = 0;
	s_line.tmp_str = 0;
	s_line.nl_len = 0;
	s_line.lo_len = 0;

	while (s_line.nl_len == 0)
	{
		if (left_over)
		{
			s_line.line = until_nl(left_over, &s_line.nl_len);
			//printf("buffer_remain: %s\n", buffer_remain);
			//printf("line.until_nl: %s\n", s_line.until_nl);
			//printf("line.until_nl_len: %ld\n", s_line.until_nl_len);
			if (s_line.line)
			{
				s_line.lo_len = ft_strlen(left_over) - s_line.nl_len;
				s_line.tmp_str = ft_substr(left_over, s_line.nl_len, s_line.lo_len);
				if (!s_line.tmp_str)
					return (NULL);
				free(left_over);
				left_over = NULL;
				if (*s_line.tmp_str)
					left_over = ft_strdup(s_line.tmp_str);
				free(s_line.tmp_str);
				s_line.tmp_str = NULL;
				return (s_line.line);
			}
			free(s_line.line);
			s_line.line = NULL;
		}

		s_line.buffer = malloc(BUFFER_SIZE + 1);
		if (!s_line.buffer)
			return (NULL);
		s_line.bytesread = read(fd, s_line.buffer, BUFFER_SIZE);
		if (s_line.bytesread == 0)
		{
			s_line.nl_len = 1;
			free (s_line.buffer);
			s_line.buffer = NULL;
			if (*left_over)
				s_line.line = ft_strdup(left_over);
			free (left_over);
			left_over = NULL;
			return (s_line.line);
		}
		else if (s_line.bytesread > 0)
		{
			s_line.tmp_str = until_nl(s_line.buffer, &s_line.nl_len);
			//printf("buffer_remain: %s\n", buffer_remain);
			//printf("line.until_nl: %s\n", s_line.until_nl);
			//printf("line.until_nl_len: %ld\n", s_line.until_nl_len);
			if (s_line.tmp_str)
			{
				if (left_over)
				{
					s_line.lo_len = ft_strlen(s_line.buffer) - s_line.nl_len + ft_strlen(left_over);
					s_line.line = ft_strjoin(left_over, s_line.tmp_str);
					free (s_line.tmp_str);
					s_line.tmp_str = NULL;
					s_line.tmp_str = ft_substr(s_line.buffer, s_line.nl_len, s_line.lo_len);
					free(left_over);
					left_over = NULL;
					left_over = ft_strdup(s_line.tmp_str);
					free (s_line.tmp_str);
					s_line.tmp_str = NULL;
					free (s_line.buffer);
					s_line.buffer = NULL;
				}
				else
				{
					s_line.lo_len = ft_strlen(s_line.buffer) - s_line.nl_len;
					s_line.line = ft_strdup(s_line.tmp_str);
					free (s_line.tmp_str);
					s_line.tmp_str = NULL;
					s_line.tmp_str = ft_substr(s_line.buffer, s_line.nl_len, s_line.lo_len);
					left_over = ft_strdup(s_line.tmp_str);
					free (s_line.tmp_str);
					s_line.tmp_str = NULL;
					free (s_line.buffer);
					s_line.buffer = NULL;
				}
			}
			else
			{
				if (!left_over)
				{
					left_over = ft_strdup(s_line.buffer);
					free(s_line.buffer);
					s_line.buffer = NULL;
				}
				else
				{
					s_line.tmp_str = ft_strdup(left_over);
					free(left_over);
					left_over = NULL;
					left_over = ft_strjoin(s_line.tmp_str, s_line.buffer);
					free (s_line.tmp_str);
					s_line.tmp_str = NULL;
					free (s_line.buffer);
					s_line.buffer = NULL;
				}
			}
		}
	}
	return (s_line.line);
}

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
		line = NULL;
	}
	close(fd);
}
