/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:33:17 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/06 20:59:55 by qbackaer         ###   ########.fr       */
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

int		get_next_line(const int fd, char **line)
{
	char *chr;
	char *rd_buffer;
	char *ln_buffer;
	static char *overflow;
	size_t ret;

	if (!fd || !line)
		return (-1);
	ln_buffer = ft_strnew(0);
	rd_buffer = ft_strnew(BUFF_SIZE);
	chr = NULL;
	if (!overflow)
		overflow = ft_strnew(0);
	else
		ln_buffer = ft_strjoin(ln_buffer, overflow);
	while ((ret = read(fd, rd_buffer, BUFF_SIZE)) > 0 && !(chr = ft_strchr(rd_buffer, SEPARATOR)))
	{
		rd_buffer[ret] = '\0';
		ln_buffer = ft_strjoin(ln_buffer, rd_buffer);
	}
	if (chr && ret > 1)
	{
		overflow = ft_strdup(chr);
		*chr = '\0';
		ln_buffer = ft_strjoin(ln_buffer, rd_buffer);
	}
	*line = ln_buffer;
	return (1);
}

int		main(void)
{
	int fd;
	char *line;

	fd = open("test", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);
	return (0);
}
