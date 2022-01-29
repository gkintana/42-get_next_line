/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:05:53 by gkintana          #+#    #+#             */
/*   Updated: 2022/01/29 12:50:50 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_free(char **stat_buff, char *set_to)
{
	free(*stat_buff);
	*stat_buff = set_to;
}

static char	*one_line(char **stat_buff)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while (stat_buff[PTR][i] != 0 && stat_buff[PTR][i] != 10)
		i++;
	if (!stat_buff[PTR][i])
	{
		line = ft_strdup(&stat_buff[PTR][0]);
		ft_free(stat_buff, NULL);
	}
	else
	{
		line = ft_substr(&stat_buff[PTR][0], 0, i + 1);
		temp = ft_strdup(&stat_buff[PTR][i + 1]);
		ft_free(stat_buff, temp);
		if (!stat_buff[PTR][0])
			ft_free(stat_buff, NULL);
	}
	return (line);
}

static void	read_fd(int fd, char **stat_buff, char *buffer, ssize_t bytes)
{
	char	*store;

	store = NULL;
	while (bytes > 0)
	{
		buffer[bytes] = 0;
		if (!stat_buff[PTR])
			stat_buff[PTR] = ft_strdup("");
		store = ft_strjoin(&stat_buff[PTR][0], buffer);
		ft_free(&stat_buff[PTR], store);
		if (ft_strchr(stat_buff[PTR], 10))
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static char	*stat_buff[1024];
	char		*buffer;
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	read_fd(fd, &stat_buff[fd], buffer, bytes);
	if (!stat_buff[fd] && bytes <= 0)
		return (NULL);
	else
		return (one_line(&stat_buff[fd]));
}
