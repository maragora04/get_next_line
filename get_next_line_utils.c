/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:16:16 by mamendes          #+#    #+#             */
/*   Updated: 2026/05/29 13:50:20 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	line_size(const char *buffer)
{
	size_t i;

	i = 0;
	if(!buffer)
		return (0);
	while(buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if(buffer[i] == '\n')
		i++;
	return (i);
}

char	*ft_linejoin(const char  *s1, const char *s2)
{
	size_t	total_len;
	char	*result;
	int	i;
	int k;

	if (!s1 && !s2)
		return (NULL);
	total_len = line_size(s1) + line_size(s2) + 1;
	result = (char *)malloc(total_len * sizeof(char));
	i = 0;
	k = 0;
	if (result == NULL)
		return (NULL);
	while(s1[i] != '\0' && s1 != NULL)
		result[k++] = s1[i++];
	k = 0;
	while(s2[k] != '\0' && s2 != NULL)
	{
		result[k++] = s2[i];
		if(s2[i++] == '\n')
			break;
	}
	result[k] = '\0';
	return (result);
}

char *isnewline(const char *s, int n)
{
	int i;

	i = 0;
	while(s[i])
	{
		if(s[i] == (char)n)
			return((char *)(s) + i);
		i++;
	}
	if(s[i] == (char)n)
		return((char *)(s) + i);
	return(NULL);
}

int newlinebuf(char *line)
{
    int i;
    int k;
    int check;

    i = 0;
    k = 0;
    check = 0;
    while (line[i])
    {
        if (line[i] == '\n')
            check = 1;    
        if (check == 1)
            line[k++] = line[i];
        i++;
    }
    while (k <= i)
        line[k++] = 0;
    return (check);
}
