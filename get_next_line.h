/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimoes <csimoes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 13:24:30 by csimoes           #+#    #+#             */
/*   Updated: 2026/11/23 23:11:38 by csimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_stash
{
	char	*data;
	size_t	len;
	size_t	cap;
}	t_stash;

char	*get_next_line(int fd);
int		gnl_has_nl(const t_stash *st);
int		gnl_ensure_cap(t_stash *st, size_t needed);
void	gnl_append(t_stash *st, const char *src, size_t n);
void	gnl_reset(t_stash *st);

#endif