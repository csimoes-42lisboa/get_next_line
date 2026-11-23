/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimoes <csimoes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 22:35:47 by csimoes           #+#    #+#             */
/*   Updated: 2026/11/23 23:11:35 by csimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_has_nl(const t_stash *st)
{
	size_t	i;

	if (!st || !st->data)
		return (0);
	i = 0;
	while (i < st->len)
	{
		if (st->data[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	gnl_ensure_cap(t_stash *st, size_t needed)
{
	char	*next;
	size_t	new_cap;
	size_t	i;

	if (needed <= st->cap && st->data)
		return (1);
	new_cap = st->cap;
	if (new_cap == 0)
		new_cap = 64;
	while (new_cap < needed)
		new_cap *= 2;
	next = malloc(new_cap);
	if (!next)
		return (0);
	i = 0;
	while (i < st->len && st->data)
	{
		next[i] = st->data[i];
		i++;
	}
	free(st->data);
	st->data = next;
	st->cap = new_cap;
	return (1);
}

void	gnl_append(t_stash *st, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		st->data[st->len] = src[i];
		st->len++;
		i++;
	}
	st->data[st->len] = '\0';
}

void	gnl_reset(t_stash *st)
{
	if (!st)
		return ;
	free(st->data);
	st->data = NULL;
	st->len = 0;
	st->cap = 0;
}
