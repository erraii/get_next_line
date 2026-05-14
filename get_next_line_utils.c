/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:08 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/14 01:34:00 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	while (n-- > 0)
		*(char *)s++ = '\0';
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*mem_copied;
	size_t	total_size;

	total_size = nmemb * size;
	if (nmemb != 0 && (size > (total_size / nmemb)))
		return (0);
	mem_copied = malloc(total_size);
	if (!mem_copied)
		return (0);
	ft_bzero(mem_copied, total_size);
	return (mem_copied);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*dst;
	size_t	src_len;
	size_t	sub_len;

	if (!s)
		return (0);
	src_len = ft_strlen(s);
	if (start >= src_len)
	{
		dst = ft_calloc(1, 1);
		if (!dst)
			return (0);
		return (dst);
	}
	if (len < (src_len - start))
		sub_len = len;
	else
		sub_len = src_len - start;
	dst = malloc((sub_len) * sizeof(char) + 1);
	if (!dst)
		return (0);
	ft_strlcpy(dst, s + start, sub_len + 1);
	return (dst);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	w_size;

	dst_size = 0;
	while ((dst_size < size) && dst[dst_size])
		dst_size++;
	src_size = 0;
	w_size = 0;
	while (src[src_size])
	{
		if (dst_size + src_size + 1 < size)
		{
			dst[dst_size + src_size] = src[src_size];
			w_size++;
		}
		src_size++;
	}
	if (dst_size < size)
		dst[dst_size + w_size] = '\0';
	return (dst_size + src_size);
}

char	*ft_strdup(const char *s)
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

char	*until_nl(char *s, size_t *len)
{
	char	*tmp;

	tmp = s;
	*len = 0;
	while (*tmp != '\0')
	{
		(*len)++;
		if (*tmp == '\n')
			return (ft_substr(s, 0, *len));
		tmp++;
	}
	return (0);
}
