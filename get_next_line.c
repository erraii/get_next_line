/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:12 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/15 16:52:08 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*ft_strdup(const char *s)
{
	int		str_len;
	char	*mem_copied;

	str_len = 0;
	while (s[str_len])
		str_len++;
	mem_copied = malloc((str_len + 1) * sizeof(char));
	if (!mem_copied)
		return (0);
	str_len = 0;
	while (s[str_len])
	{
		mem_copied[str_len] = s[str_len];
		str_len++;
	}
	mem_copied[str_len] = '\0';
	return (mem_copied);
}

static char	*until_nl(char *s, size_t *len)
{
	size_t	i;

	*len = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
		{
			*len = i + 1;
			return (ft_substr(s, 0, *len));
		}
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	t_getline	s_line;
	static char	*left_over;

	s_line.line = NULL;
	s_line.buffer = NULL;
	s_line.tmp_str = NULL;
	s_line.nl_len = 0;
	s_line.lo_len = 0;
	while (s_line.nl_len == 0)
	{
		if (left_over)
		{
			s_line.line = until_nl(left_over, &s_line.nl_len);
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
			if (left_over && *left_over)
				s_line.line = ft_strdup(left_over);
			free (left_over);
			left_over = NULL;
			return (s_line.line);
		}
		else if (s_line.bytesread > 0)
		{
			s_line.buffer[BUFFER_SIZE] = '\0';
			s_line.tmp_str = until_nl(s_line.buffer, &s_line.nl_len);
			if (s_line.tmp_str)
			{
				if (left_over)
				{
					s_line.lo_len = ft_strlen(s_line.buffer) - s_line.nl_len + ft_strlen(left_over);
					s_line.line = ft_strjoin(left_over, s_line.tmp_str);
					free (s_line.tmp_str);
					s_line.tmp_str = ft_substr(s_line.buffer, s_line.nl_len, s_line.lo_len);
					free(left_over);
					left_over = ft_strdup(s_line.tmp_str);
					free (s_line.tmp_str);
					free (s_line.buffer);
				}
				else
				{
					s_line.lo_len = ft_strlen(s_line.buffer) - s_line.nl_len;
					s_line.line = ft_strdup(s_line.tmp_str);
					free (s_line.tmp_str);
					s_line.tmp_str = ft_substr(s_line.buffer, s_line.nl_len, s_line.lo_len);
					left_over = ft_strdup(s_line.tmp_str);
					free (s_line.tmp_str);
					free (s_line.buffer);
				}
			}
			else
			{
				if (!left_over)
				{
					left_over = ft_strdup(s_line.buffer);
					free(s_line.buffer);
				}
				else
				{
					s_line.tmp_str = ft_strdup(left_over);
					free(left_over);
					left_over = NULL;
					left_over = ft_strjoin(s_line.tmp_str, s_line.buffer);
					free (s_line.tmp_str);
					free (s_line.buffer);
				}
			}
		}
		else
		{
			free (s_line.buffer);
			return(NULL);
		}
	}
	return (s_line.line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("1char.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	for (int i = 0; i < 1; i++)
// 	{
// 		line = get_next_line(fd);
// 		printf("line[%d]: %s", i + 1, line);
// 		free (line);
// 		line = NULL;
// 	}
// 	close(fd);
// }
