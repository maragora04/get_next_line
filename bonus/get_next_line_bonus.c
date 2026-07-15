/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:59:54 by mamendes          #+#    #+#             */
/*   Updated: 2026/07/15 08:57:46 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_join(int fd, char *line, char *buffer, int *done)
{
	int	bytesread;

	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread < 0)
	{
		*done = 2;
		buffer[0] = '\0';
		return (free(line), NULL);
	}
	if (bytesread == 0)
	{
		*done = 1;
		buffer[0] = '\0';
		return (line);
	}
	buffer[bytesread] = '\0';
	line = ft_linejoin(line, buffer);
	if (!line)
	{
		*done = 2;
		return (NULL);
	}
	if (newlinebuf(buffer))
		*done = 1;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			done;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	done = 0;
	while (!done)
	{
		if (buffer[fd][0] != '\0')
		{
			line = beeline(line, buffer[fd]);
			if (!line)
				return (NULL);
			if (isnewline(line))
				return (line);
		}
		line = read_and_join(fd, line, buffer[fd], &done);
		if (done == 2)
			return (NULL);
	}
	return (line);
}
/* int main()
{
	int fd1 = open("test1", O_RDONLY);
	int fd2 = open("test2", O_RDONLY);
	int fd3 = open("test3",  O_RDONLY);
	int fd4 = open("test4",  O_RDONLY);
	char *str1;
	char *str2;
	char *str3;
	char *str4;
	str1 = get_next_line(fd1);
	str2 = get_next_line(fd2);
	str3 = get_next_line(fd3);
	str4 = get_next_line(fd4);
	
	printf("%s", str1);
	free(str1);
	printf("%s", str2);
	free(str2);
	printf("%s", str3);
	free(str3);
	printf("%s", str4);
	free(str4);
	str1 = get_next_line(fd1);
	str2 = get_next_line(fd2);
	str3 = get_next_line(fd3);
	str4 = get_next_line(fd4);
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	return 0;
}  */