/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:05:53 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/02 18:48:11 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_static_buffer(char *buffer)
{
	char	*temp;
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != 10)
		i++;
	if (!buffer[i])
	{
		free(buffer);
		buffer = NULL;
	}
	else
	{
		temp = ft_strdup(buffer + i + 1);
		free(buffer);
		buffer = temp;
	}
	return (buffer);
}

static char	*one_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != 10)
		i++;
	line = ft_substr(buffer, 0, i + 1);
	return (line);
}

static char	*read_fd(int fd, char *buffer, char *read_str)
{
	char	*temp;
	ssize_t	bytes;

	bytes = read(fd, read_str, BUFFER_SIZE);
	if (!buffer)
		buffer = ft_strdup("");
	while (bytes > 0)
	{
		read_str[bytes] = 0;
		temp = ft_strjoin(buffer, read_str);
		free(buffer);
		buffer = temp;
		if (ft_strchr(buffer, 10))
			break ;
		bytes = read(fd, read_str, BUFFER_SIZE);
	}
	free(read_str);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*string[2];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	string[0] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!string[0])
		return (NULL);
	buffer = read_fd(fd, buffer, string[0]);
	if (!buffer || !buffer[0])
		return (NULL);
	string[1] = one_line(buffer);
	buffer = update_static_buffer(buffer);
	return (string[1]);
}
