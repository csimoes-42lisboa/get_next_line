/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimoes <csimoes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 10:04:08 by csimoes           #+#    #+#             */
/*   Updated: 2026/11/20 23:15:04 by csimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	rloop(int fd, char **stash, char *buffer, int er)
{
	char	*temp;
	ssize_t	br;

	br = 1;
	while (ft_strchr(*stash, '\n') == NULL && br != 0)
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br <= 0)
		{
			if (br == -1)
				er = -1;
			break ;
		}
		buffer[br] = '\0';
		temp = ft_strjoingnl(*stash, buffer);
		if (temp)
		{
			free(*stash);
			*stash = temp;
		}
		else
		{
			er = -1;
			break ;
		}
	}
	return (er);
}

static int	readstash(int fd, char **stash)
{
	char	*buffer;
	ssize_t	bytesread;
	char	*temp;
	int		error;

	error = 0;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytesread = 1;
	free(buffer);
	return (error);
}

char	*get_next_line(int fd)
{
	static char *stash;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (readstash(fd, &stash) == -1)
		return (NULL);
}