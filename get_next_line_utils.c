/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:08 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/17 14:17:27 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

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

char	*join_line(char *line, char *add)
{
	char	*new_line;
	size_t	line_len;
	size_t	add_len;

	if (!add)
		return (line);
	line_len = ft_strlen(line);
	add_len = ft_strlen(add);
	new_line = malloc(line_len + add_len + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	if (line)
		ft_strlcpy(new_line, line, line_len + 1);
	else
		new_line[0] = '\0';
	ft_strlcpy(new_line + line_len, add, add_len + 1);
	free(line);
	return (new_line);
}

char	*till_nl(const char *s, char **rem)
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

int	use_remain(t_gl *s_line, char *remain)
{
	s_line->line = till_nl(remain, &s_line->tmp);
	if (!s_line->line || !s_line->tmp)
		return (0);
	if (*s_line->line)
	{
		ft_strlcpy(remain, s_line->tmp, ft_strlen(s_line->tmp) + 1);
		free(s_line->tmp);
		s_line->tmp = NULL;
		s_line->nl_found = 1;
		return (1);
	}
	free(s_line->line);
	s_line->line = NULL;
	s_line->line = join_line(s_line->line, s_line->tmp);
	free(s_line->tmp);
	s_line->tmp = NULL;
	remain[0] = '\0';
	return (1);
}
