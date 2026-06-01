/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:59:54 by mamendes          #+#    #+#             */
/*   Updated: 2026/06/01 14:54:53 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char *get_next_line(int fd)
{
	int         bytesread;
	static char buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char        *line;

	line = NULL;
	while (1)
	{
		if (buffer[fd][0] != '\0')
			if(beeline(line, buffer[fd]))
				return(line);
		bytesread = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytesread < 0)
			return (free(line), NULL);
		if (bytesread == 0)
			return (newlinebuf(buffer[fd]), line);
		buffer[fd][bytesread] = '\0';
		line = ft_linejoin(line, buffer[fd]);
		if (!line)
			return (NULL);
		if (newlinebuf(buffer[fd]))
			break ;
	}
	return (line);
}
/* int main()
{
	int fd1 = open("test1", O_RDONLY);
	int fd2 = open("test2", O_RDONLY);
	int fd3 = open("test3",  O_RDONLY);
		char *str1;
	char *str2;
	char *str3;
	str1 = get_next_line(fd1);
	str2 = get_next_line(fd2);
	str3 = get_next_line(fd3);
	while (str1)
	{
		printf("%s", str1);
		free(str1);
		printf("%s", str2);
		free(str2);
		printf("%s", str3);
		free(str3);
		str1 = get_next_line(fd1);
		str2 = get_next_line(fd2);
		str3 = get_next_line(fd3);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return 0;
} */
