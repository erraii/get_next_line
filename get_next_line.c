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
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (*(src + src_len))
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (*(src + i) && (i < (size - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

static char	*till_nl(const char *s, char **rem)
{
	size_t	i;
	char	*res;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	else
		i = 0;
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	*rem = malloc(ft_strlen(s + i) + 1);
	if (!*rem)
	{
		free(res);
		return (NULL);
	}
	ft_strlcpy(res, s, i + 1);
	ft_strlcpy(*rem, s + i, ft_strlen(s + i) + 1);
	return (res);
}

char	*get_next_line(int fd)
{
	t_gl	s_line;
	static char	remain[BUFFER_SIZE + 1];

	s_line.line = NULL;
	s_line.tmp = NULL;
	s_line.buffer = NULL;
	s_line.nl_found = 0;
	if (*remain)
	{
		//printf("remainde line aranıyor\n");
		s_line.line = till_nl(remain, &s_line.tmp);
		if (!s_line.line || !s_line.tmp)
		{
			free(s_line.line);
			free(s_line.tmp);
			return (NULL);
		}
		if (*s_line.line)
		{
			ft_strlcpy(remain, s_line.tmp, ft_strlen(s_line.tmp) + 1);
			free(s_line.tmp);
			return(s_line.line);
		}
		free(s_line.line);
		free(s_line.tmp);
		s_line.line = malloc(ft_strlen(remain) + 1);
		if (!s_line.line)
			return (NULL);
		ft_strlcpy(s_line.line, remain, ft_strlen(remain) + 1);
		remain[0] = '\0';
	}
	//printf("remainde line yok\n");
	while (s_line.nl_found == 0)
	{
		s_line.b_read = read(fd, remain, BUFFER_SIZE);
		if (s_line.b_read == 0)
		{
			remain[0] = '\0';
			s_line.nl_found = 1;
		}
		else if (s_line.b_read > 0)
		{
			remain[s_line.b_read] = '\0';
			//printf("okundu: %s\n", remain);
			s_line.buffer = till_nl(remain, &s_line.tmp);
			remain[0] = '\0';
			if (!s_line.buffer || !s_line.tmp)
			{
				free(s_line.buffer);
				free(s_line.tmp);
				return (NULL);
			}
			if (*s_line.buffer)
			{
				//printf("döngü: remainde line bulundu\n");
				//printf("buffer: %s\n", s_line.buffer);
				//printf("remain: %s\n", s_line.tmp);
				ft_strlcpy(remain, s_line.tmp, ft_strlen(s_line.tmp) + 1);
				free(s_line.tmp);
				if (s_line.line)
				{
					s_line.tmp = malloc(ft_strlen(s_line.line) + 1);
					if(!s_line.tmp)
						return(NULL);
					ft_strlcpy(s_line.tmp, s_line.line, ft_strlen(s_line.line) + 1);
					free(s_line.line);
					s_line.line = malloc(ft_strlen(s_line.tmp) + ft_strlen(s_line.buffer) + 1);
					if(!s_line.line)
						return(NULL);
					ft_strlcpy(s_line.line, s_line.tmp, ft_strlen(s_line.tmp) + 1);
					free(s_line.tmp);
					ft_strlcpy(s_line.line + ft_strlen(s_line.line), s_line.buffer, ft_strlen(s_line.buffer) + 1);
					free(s_line.buffer);
				}
				else
				{
					//printf("döngü: remainde line var, s_line yok\n");
					s_line.line = malloc(ft_strlen(s_line.buffer) + 1);
					if(!s_line.line)
						return(NULL);
					ft_strlcpy(s_line.line, s_line.buffer, ft_strlen(s_line.buffer) + 1);
					free(s_line.buffer);
				}
				s_line.nl_found = 1;
			}
			else
			{
				//printf("döngü: remainde line yok\n");
				free(s_line.buffer);
				if (s_line.line)
				{
					s_line.buffer = malloc(ft_strlen(s_line.line) + 1);
					ft_strlcpy(s_line.buffer, s_line.line, ft_strlen(s_line.line) + 1);
					free(s_line.line);
					s_line.line = malloc(ft_strlen(s_line.buffer) + ft_strlen(s_line.tmp) + 1);
					ft_strlcpy(s_line.line, s_line.buffer, ft_strlen(s_line.buffer) + 1);
					free(s_line.buffer);
					ft_strlcpy(s_line.line + ft_strlen(s_line.line), s_line.tmp, ft_strlen(s_line.tmp) + 1);
					free(s_line.tmp);
				}
				else
				{
					s_line.line = malloc(ft_strlen(s_line.tmp) + 1);
					ft_strlcpy(s_line.line, s_line.tmp, ft_strlen(s_line.tmp) + 1);
					free(s_line.tmp);
				}
			}
		}
		else
		{
			/*s_line.nl_found = 0;
			while (s_line.nl_found < BUFFER_SIZE + 1)
			{
				remain[s_line.nl_found] = '\0';
				s_line.nl_found++;
			}
 			if (s_line.buffer)
				free(s_line.buffer);
			if (s_line.line)
				free(s_line.line); */
			if (s_line.tmp)
				free(s_line.tmp);
			return (NULL);
		}
		//free(s_line.buffer);
	}
	return(s_line.line);
}

/* int	main(void)
{
	int		fd;
	char	*line; */
/* 	char	*remain;
	char	*s; */

/* 	s = "abc\ndef";
	line = till_nl(s, &remain);
	printf("line: %s", line);
	printf("remain: %s", remain);
	free(line);
	free(remain); */
/* 	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	for (int i = 0; i < 52; i++)
	{
		line = get_next_line(fd);
		if(line)
			printf("line[%d]: %s", i + 1, line);
		free (line);
		line = NULL;
	}
	close(fd);
} */
