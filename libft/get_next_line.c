/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:17:00 by yopeng            #+#    #+#             */
/*   Updated: 2025/11/26 17:26:30 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_ft_strjoin(char *s1, char *s2);

static char	*free_and_null(char **p1, char **p2)
{
	if (p1 && *p1)
	{
		free (*p1);
		*p1 = NULL;
	}
	if (p2 && *p2)
	{
		free (*p2);
		*p2 = NULL;
	}
	return (NULL);
}

static char	*read_until_newline(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes_read;

	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read (fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_and_null(&buf, &stash));
		buf[bytes_read] = '\0';
		stash = gnl_ft_strjoin(stash, buf);
		if (!stash)
			return (free_and_null(&buf, NULL));
	}
	free (buf);
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	int		i;

	if (!stash || *stash == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static char	*update_stash(char *stash)
{
	char	*new_stash;
	size_t	start;

	if (!stash)
		return (NULL);
	start = 0;
	while (stash[start] && stash[start] != '\n')
		start++;
	if (!stash[start])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(stash + start + 1);
	free(stash);
	if (!new_stash)
		return (NULL);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd == -1)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_until_newline(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(stash);
	return (line);
}
