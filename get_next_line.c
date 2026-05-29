/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:16:23 by mamendes          #+#    #+#             */
/*   Updated: 2026/05/29 13:39:07 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    int         bytesread;
    static char buffer[BUFFER_SIZE + 1];
    char        *line;
    char        *tmp;

    line = NULL;
    while (!isnewline(buffer, '\n'))
    {
        bytesread = read(fd, buffer, BUFFER_SIZE);
        if (bytesread <= 0)
        {
            if (buffer[0] == '\0')
                return (free(line), NULL);
            break ;
        }
        buffer[bytesread] = '\0';
        tmp = ft_linejoin(line, buffer);
        free(line);
        line = tmp;
        if (!line)
            return (NULL);
        newlinebuf(buffer);
    }
    if (isnewline(buffer, '\n'))
    {
        tmp = ft_linejoin(line, buffer);
        free(line);
        line = tmp;
        newlinebuf(buffer);
    }
    return (line);
}
