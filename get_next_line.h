/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:19 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/15 10:04:55 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>

typedef struct s_getline
{
	char	*buffer;
	char	*tmp_str;
	char	*line;
	size_t	nl_len;
	size_t	lo_len;
	ssize_t	bytesread;
}	t_getline;

char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*until_nl(char *s, size_t *len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char *s, size_t start, size_t len);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);
char		*ft_substr(char *s, size_t start, size_t len);

#endif