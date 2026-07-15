/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:16:26 by mamendes          #+#    #+#             */
/*   Updated: 2026/07/15 12:25:17 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdint.h>
# include <fcntl.h>

typedef struct s_line
{
	char	*str;
	size_t	len;
	size_t	cap;
}	t_line;

char	*get_next_line(int fd);
char	*ft_linejoin(char *s1, char *s2);
size_t	line_size(const char *buffer);
char	*isnewline(const char *s);
int		newlinebuf(char *line);
char	*beeline(t_line *l, char *buffer);
int		line_append(t_line *l, char *chunk);
int		line_grow(t_line *l, size_t need);

#endif
