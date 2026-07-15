/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:16:23 by mamendes          #+#    #+#             */
/*   Updated: 2026/07/15 12:33:38 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line_append(t_line *l, char *chunk)
{
	size_t	chunk_len;
	size_t	i;

	chunk_len = line_size(chunk);
	if (l->len + chunk_len + 1 > l->cap)
		if (!line_grow(l, l->len + chunk_len + 1))
			return (0);
	i = 0;
	while (i < chunk_len)
	{
		l->str[l->len + i] = chunk[i];
		i++;
	}
	l->len += chunk_len;
	l->str[l->len] = '\0';
	return (1);
}

static int	read_and_join(int fd, t_line *l, char *buffer)
{
	int	bytesread;

	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread < 0)
	{
		buffer[0] = '\0';
		return (free(l->str), l->str = NULL, 2);
	}
	if (bytesread == 0)
	{
		buffer[0] = '\0';
		return (1);
	}
	buffer[bytesread] = '\0';
	if (!line_append(l, buffer))
		return (free(l->str), l->str = NULL, 2);
	if (newlinebuf(buffer))
		return (1);
	return (0);
}

char	*beeline(t_line *l, char *buffer)
{
	if (buffer[0] != '\0')
	{
		if (!line_append(l, buffer))
			return (free(l->str), l->str = NULL, NULL);
		newlinebuf(buffer);
	}
	return (l->str);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	t_line		l;
	int			flag;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	l.str = NULL;
	l.len = 0;
	l.cap = 0;
	flag = 0;
	while (!flag)
	{
		if (buffer[0] != '\0')
		{
			if (!beeline(&l, buffer))
				return (NULL);
			if (isnewline(l.str))
				return (l.str);
		}
		flag = read_and_join(fd, &l, buffer);
		if (flag == 2)
			return (NULL);
	}
	return (l.str);
}

/* int main()
{
	int fd1 = open("test1", O_RDONLY);
	char *str1;
	str1 = get_next_line(fd1);
	printf("%s", str1);
	free(str1);
	close(fd1);
	return 0;
} */
