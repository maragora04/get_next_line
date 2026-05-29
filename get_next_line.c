/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:16:23 by mamendes          #+#    #+#             */
/*   Updated: 2026/05/29 19:17:48 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    int         bytesread;
    static char buffer[BUFFER_SIZE + 1];
    char        *line;

    line = NULL;
    while (1)
    {
        if (buffer[0] != '\0')
        {
            line = ft_linejoin(line, buffer);
            newlinebuf(buffer);
            if (isnewline(line))
                return (line);
        }
        bytesread = read(fd, buffer, BUFFER_SIZE);
        if (bytesread < 0)
            return (free(line), NULL);
        if (bytesread == 0)
            return (newlinebuf(buffer), line);
        buffer[bytesread] = '\0';
        line = ft_linejoin(line, buffer);
        if (!line)
            return (NULL);
        if (newlinebuf(buffer))
            break ;
    }
    return (line);
}

/* int main()
{
	int fd1 = open("text", O_RDONLY);
	// int fd2 = open("bonus2.txt", O_RDONLY);
	// int fd3 = open("bonus3.txt", O_RDONLY);
	char *str1;
	// char *str2;
	// char *str3;
	str1 = get_next_line(fd1);
	// str2 = get_next_line(fd2);
	// str3 = get_next_line(fd3);
	while (str1)
	{
		printf("%s", str1);
		free(str1);
		// printf("%s", str2);
		// free(str2);
		// printf("%s", str3);
		// free(str3);
		str1 = get_next_line(fd1);
		// str2 = get_next_line(fd2);
		// str3 = get_next_line(fd3);
	}
	close(fd1);
	// close(fd2);
	// close(fd3);
	return 0;
} */
