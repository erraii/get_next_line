/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 10:47:19 by ecakiray          #+#    #+#             */
/*   Updated: 2026/05/15 16:47:57 by ecakiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>

typedef struct s_gl
{
	char	*buffer;
	char	*tmp;
	char	*line;
	ssize_t	b_read;
	size_t	nl_found;
}	t_gl;

#endif
