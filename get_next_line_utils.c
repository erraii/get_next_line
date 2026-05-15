/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:08 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/15 16:47:27 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

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
		dst = malloc(1);
		if (!dst)
			return (0);
		dst[0] = '\0';
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	size_t	sjoin_len;
	size_t	b_zero;

	if (!s1 || !s2)
		return (0);
	sjoin_len = ft_strlen(s1);
	sjoin_len += ft_strlen(s2) + 1;
	sjoin = malloc (sjoin_len);
	if (!sjoin)
		return (0);
	b_zero = 0;
	while (sjoin_len > b_zero)
	{
		sjoin[b_zero] = '\0';
		b_zero++;
	}
	ft_strlcat(sjoin, s1, sjoin_len);
	ft_strlcat(sjoin, s2, sjoin_len);
	return (sjoin);
}
