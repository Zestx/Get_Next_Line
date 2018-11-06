/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:33:17 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/06 18:55:28 by qbackaer         ###   ########.fr       */
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
	size_t ret;
	char *rd_buffer;
	char *ln_buffer;
	char *chr;
	static char *ovf_line;
	if (!line || fd < 0)
		return (-1);
	rd_buffer = malloc(BUFF_SIZE + 1);
	while ((ret = read(fd, rd_buffer, BUFF_SIZE)) > 0 && !(chr = ft_strchr(rd_buffer, '\n')))
	{
		rd_buffer[ret] = '\0';
		ln_buffer = ft_strjoin(ln_buffer, rd_buffer);
	}
	if (chr)
		strcpy(ovf_line, chr);
	*chr = '\0';
	*line = ln_buffer;
	return (1);
}

int		main(void)
{
	int fd;
	char *line[1000];

	fd = open("TODO", O_RDONLY);
	get_next_line(fd, line);
	printf("%s\n", *line);
	return (0);
}
