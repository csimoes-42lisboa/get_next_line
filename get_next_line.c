/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimoes <csimoes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 10:04:08 by csimoes           #+#    #+#             */
/*   Updated: 2026/11/22 18:50:51 by csimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *stash)
{

}

static void	rloop(int fd, char **stash, char *buffer, int *br)
{
	char	*temp;

	while (ft_strchr(*stash, '\n') == NULL && *br > 0)
	{
		*br = read(fd, buffer, BUFFER_SIZE);
		if (*br > 0)
		{
			buffer[*br] = '\0';
			temp = ft_strjoingnl(*stash, buffer);
			if (temp)
			{
				free(*stash);
				*stash = temp;
			}
			else
				*br = -1;
		}
	}
}

static int	readstash(int fd, char **stash)
{
	char	*buffer;
	ssize_t	bytesread;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytesread = 1;
	rloop(fd, stash, buffer, &bytesread);
	free(buffer);
	if (bytesread == -1)
		return (-1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (readstash(fd, &stash) == -1)
		return (NULL);
	if (stash[0] == '\0')
		return (NULL);
	line = extract_line(stash);
}
