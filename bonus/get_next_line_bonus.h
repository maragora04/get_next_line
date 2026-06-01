/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:03:00 by mamendes          #+#    #+#             */
/*   Updated: 2026/06/01 15:04:38 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
#include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_linejoin(char  *s1, char *s2);
size_t	line_size(const char *buffer);
char	*isnewline(const char *s);
int		newlinebuf(char *line);
char	*beeline(char *line, char *buffer);

#endif