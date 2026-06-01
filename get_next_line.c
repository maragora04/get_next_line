/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:16:23 by mamendes          #+#    #+#             */
/*   Updated: 2026/06/01 15:24:27 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			bytesread;
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	while (1)
	{
		if (buffer[0] != '\0')
			if (beeline(line, buffer))
				return (line);
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