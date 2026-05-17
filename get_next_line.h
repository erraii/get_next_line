/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:19 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/17 14:17:43 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*join_line(char *line, char *add);
char	*till_nl(const char *s, char **rem);
int		use_remain(t_gl *s_line, char *remain);

typedef struct s_gl
{
	char	*buffer;
	char	*tmp;
	char	*line;
	ssize_t	b_read;
	size_t	nl_found;
}	t_gl;

#endif