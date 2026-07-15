/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:16:16 by mamendes          #+#    #+#             */
/*   Updated: 2026/07/15 12:25:05 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	line_size(const char *buffer)
{
	size_t	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (i);
}

char	*ft_linejoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*result;
	int		i;
	int		k;

	if (!s1 && !s2)
		return (NULL);
	total_len = (line_size(s1) + line_size(s2)) + 1;
	result = (char *)malloc(total_len * sizeof(char));
	if (result == NULL)
		return (free(s1), NULL);
	i = 0;
	k = 0;
	while (s1 != NULL && s1[i] != '\0')
		result[k++] = s1[i++];
	i = 0;
	while (s2 != NULL && s2[i] != '\0')
	{
		result[k++] = s2[i];
		if (s2[i++] == '\n')
			break ;
	}
	result[k] = '\0';
	free(s1);
	return (result);
}

char	*isnewline(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return ((char *)(s) + i);
		i++;
	}
	if (s[i] == '\n')
		return ((char *)(s) + i);
	return (NULL);
}

int	newlinebuf(char *line)
{
	int	i;
	int	k;
	int	check;

	i = 0;
	k = 0;
	check = 0;
	while (line[i])
	{
		if (check == 1)
			line[k++] = line[i];
		if (line[i] == '\n')
			check = 1;
		i++;
	}
	while (k <= i)
		line[k++] = 0;
	return (check);
}

int	line_grow(t_line *l, size_t need)
{
	char	*new_str;
	size_t	i;

	if (l->cap == 0)
		l->cap = 64;
	while (l->cap < need)
		l->cap *= 2;
	new_str = (char *)malloc(l->cap);
	if (!new_str)
		return (0);
	i = 0;
	while (i < l->len)
	{
		new_str[i] = l->str[i];
		i++;
	}
	free(l->str);
	l->str = new_str;
	return (1);
}
