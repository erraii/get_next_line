/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:08 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/17 14:38:47 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

char	*join_line(char *line, char *add)
{
	char	*new_line;
	size_t	i;
	size_t	j;

	if (!add)
		return (line);
	new_line = malloc(ft_strlen(line) + ft_strlen(add) + 1);
	if (!new_line)
		return (free(line), NULL);
	i = 0;
	while (line && line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	j = 0;
	while (add[j])
		new_line[i++] = add[j++];
	new_line[i] = '\0';
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
		return (free(res), NULL);
	ft_strlcpy(res, s, i + 1);
	ft_strlcpy(*rem, s + i, ft_strlen(s + i) + 1);
	return (res);
}
