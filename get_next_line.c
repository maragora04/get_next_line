/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamendes <mamendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:16:23 by mamendes          #+#    #+#             */
/*   Updated: 2026/05/25 16:12:07 by mamendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
char *get_next_line(int fd)
{
	int bytesread;
	static char	buffer[BUFFER_SIZE + 1];

	if(!buffer)
		return (NULL);
	bytesread = read(fd, buffer, 3);
	if(bytesread <= 0)
		return (NULL);
	while(bytesread && bytesread != '\0')
	{
		
	}
}
