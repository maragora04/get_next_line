/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:16:23 by mamendes          #+#    #+#             */
/*   Updated: 2026/07/15 08:58:07 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_join(int fd, char *line, char *buffer, int *flag)
{
	int	bytesread;

	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread < 0)
	{
		*flag = 2;
		buffer[0] = '\0';
		return (free(line), NULL);
	}
	if (bytesread == 0)
	{
		*flag = 1;
		buffer[0] = '\0';
		return (line);
	}
	buffer[bytesread] = '\0';
	line = ft_linejoin(line, buffer);
	if (!line)
	{
		*flag = 2;
		return (NULL);
	}
	if (newlinebuf(buffer))
		*flag = 1;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			flag;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	flag = 0;
	while (!flag)
	{
		if (buffer[0] != '\0')
		{
			line = beeline(line, buffer);
			if (!line)
				return (NULL);
			if (isnewline(line))
				return (line);
		}
		line = read_and_join(fd, line, buffer, &flag);
		if (flag == 2)
			return (NULL);
	}
	return (line);
}

/* int main()
{
	int fd1 = open("test1", O_RDONLY);
	char *str1;
	str1 = get_next_line(fd1);
	printf("%s", str1);
	free(str1);
	// str1 = get_next_line(fd1);
	// printf("%s", str1);
	// free(str1);
	// str1 = get_next_line(fd1);
	// printf("%s", str1);
	// free(str1);
	close(fd1);
	return 0;
} */
/* int main()
{
	int fd1 = open("test1", O_RDONLY);
	char *str1;
	str1 = get_next_line(fd1);
	while (str1)
	{
		printf("%s", str1);
		free(str1);
		str1 = get_next_line(fd1);
	}
	close(fd1);
	return 0;
} */