/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:12 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/17 15:57:46 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

static void	init_line(t_gl *s)
{
	s->buffer = NULL;
	s->tmp = NULL;
	s->line = NULL;
	s->b_read = 0;
	s->nl_found = 0;
}

static char	*free_null(t_gl *s)
{
	free(s->buffer);
	free(s->tmp);
	free(s->line);
	return (NULL);
}

static int	use_remain(t_gl *s, char *remain)
{
	s->buffer = till_nl(remain, &s->tmp);
	if (!s->buffer || !s->tmp)
		return (0);
	if (*s->buffer)
	{
		ft_strlcpy(remain, s->tmp, ft_strlen(s->tmp) + 1);
		s->line = join_line(s->line, s->buffer);
		s->nl_found = 1;
	}
	else
	{
		s->line = join_line(s->line, s->tmp);
		remain[0] = '\0';
	}
	free(s->buffer);
	free(s->tmp);
	s->buffer = NULL;
	s->tmp = NULL;
	return (s->line != NULL);
}

static int	read_part(int fd, t_gl *s, char *remain)
{
	s->b_read = read(fd, remain, BUFFER_SIZE);
	if (s->b_read == 0)
	{
		remain[0] = '\0';
		s->nl_found = 1;
		return (1);
	}
	if (s->b_read < 0)
	{
		remain[0] = '\0';
		return (0);
	}
	remain[s->b_read] = '\0';
	if (!use_remain(s, remain))
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	remain[OPEN_MAX][BUFFER_SIZE + 1];
	t_gl		s;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	init_line(&s);
	if (*remain[fd] && !use_remain(&s, remain[fd]))
		return (free_null(&s));
	while (!s.nl_found)
	{
		if (!read_part(fd, &s, remain[fd]))
			return (free_null(&s));
	}
	return (s.line);
}

// int	main(void)
// {
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	char	*line1;
// 	char	*line2;
// 	char	*line3;
/* 	char	*remain;
	char	*s; 

 	s = "abc\ndef";
	line = till_nl(s, &remain);
	printf("line: %s", line);
	printf("remain: %s", remain);
	free(line);
	free(remain); */
// 	fd1 = open("giant_line.txt", O_RDONLY);
// 	fd2 = open("test.txt", O_RDONLY);
// 	fd3 = open("1char.txt", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
// 		return (1);
// 	for (int i = 0; i < 52; i++)
// 	{
// 		line1 = get_next_line(fd1);
// 		if (line1)
// 			printf("line[%d] of file1: %s", i + 1, line1);
// 		free (line1);
// 		line1 = NULL;
// 		line2 = get_next_line(fd2);
// 		if (line2)
// 			printf("line[%d] of file2: %s", i + 1, line2);
// 		free (line2);
// 		line2 = NULL;
// 		line3 = get_next_line(fd3);
// 		if (line3)
// 			printf("line[%d] of file3: %s", i + 1, line3);
// 		free (line3);
// 		line3 = NULL;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// }