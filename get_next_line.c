/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimoes <csimoes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 22:35:32 by csimoes           #+#    #+#             */
/*   Updated: 2026/11/23 23:11:36 by csimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_to_stash(int fd, t_stash *st)
{
	char	*buf;
	ssize_t	br;

	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (-1);
	br = 1;
	while (!gnl_has_nl(st) && br > 0)
	{
		br = read(fd, buf, BUFFER_SIZE);
		if (br < 0)
			return (free(buf), -1);
		if (br > 0)
		{
			if (!gnl_ensure_cap(st, st->len + (size_t)br + 1))
				return (free(buf), -1);
			gnl_append(st, buf, (size_t)br);
		}
	}
	free(buf);
	return (0);
}

static char	*extract_line(t_stash *st)
{
	size_t	cut;
	size_t	i;
	char	*line;

	if (!st->data || st->len == 0)
		return (NULL);
	cut = 0;
	while (cut < st->len && st->data[cut] != '\n')
		cut++;
	if (cut < st->len && st->data[cut] == '\n')
		cut++;
	line = malloc(cut + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < cut)
	{
		line[i] = st->data[i];
		i++;
	}
	line[cut] = '\0';
	return (line);
}

static void	clean_stash(t_stash *st)
{
	size_t	cut;
	size_t	i;

	cut = 0;
	while (cut < st->len && st->data[cut] != '\n')
		cut++;
	if (cut < st->len && st->data[cut] == '\n')
		cut++;
	if (cut >= st->len)
	{
		gnl_reset(st);
		return ;
	}
	i = 0;
	while (i + cut < st->len)
	{
		st->data[i] = st->data[i + cut];
		i++;
	}
	st->len -= cut;
	st->data[st->len] = '\0';
}

char	*get_next_line(int fd)
{
	static t_stash	st;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_to_stash(fd, &st) < 0)
		return (gnl_reset(&st), NULL);
	line = extract_line(&st);
	if (!line)
		return (gnl_reset(&st), NULL);
	clean_stash(&st);
	return (line);
}
