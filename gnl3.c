/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:33:17 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/07 19:10:36 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "header.h"
#include "libft.h"

char	*read_until(const int fd, char **leftover)
{
	char	*rd_buffer;
	char	*ln_buffer;
	size_t	ret;
	char	*chr;

	rd_buffer = ft_strnew(BUFF_SIZE);
	ln_buffer = ft_strnew(0);
	chr = NULL;
	while ((ret = read(fd, rd_buffer, BUFF_SIZE)) > 0
			&& !ft_strchr(rd_buffer, SEPARATOR))
	{
		rd_buffer[ret] = '\0';
		ln_buffer = ft_strjoin(ln_buffer, rd_buffer);
	}
	if (ret > 0)
		ln_buffer = ft_strjoin(ln_buffer, rd_buffer);
	if ((chr = ft_strchr(ln_buffer, SEPARATOR)))
	{
		if (ret > 1)
			*leftover = ft_strdup(chr + 1);
		*chr = '\0';
	}
	return (ln_buffer);
}

int		get_next_line(const int fd, char **line)
{
	char		*lo_chr;
	char		*buffer;
	static char	*leftover;

	if (!fd || !line)
		return (-1);
	buffer = ft_strnew(0);
	if (leftover)
	{
		buffer = ft_strjoin(buffer, leftover);
		if ((lo_chr = strchr(buffer, SEPARATOR)))
		{
			leftover = ft_strdup(lo_chr + 1);
			*lo_chr = '\0';
			*line = buffer;
			return (1);
		}
		else
			ft_bzero(leftover, ft_strlen(leftover));
	}
	buffer = ft_strjoin(buffer, read_until(fd, &leftover));
	*line = buffer;
	return (1);
}

int		main(void)
{
	int		fd;
	char	*line;

	fd = open("test", O_RDONLY);
	get_next_line(fd, &line);
	printf("> %s ||\n", line);
	get_next_line(fd, &line);
	printf("> %s ||\n", line);
	get_next_line(fd, &line);
	printf("> %s ||\n", line);
	get_next_line(fd, &line);
	printf("> %s ||\n", line);
	get_next_line(fd, &line);
	printf("> %s ||\n", line);
	return (0);
}
