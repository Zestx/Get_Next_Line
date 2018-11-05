/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 21:00:43 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/05 20:55:22 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "header.h"
#include "libft.h"
#include <string.h>

int		get_next_line(const int fd, char **line)
{
	size_t rdd;
	char *buffer[BUFF_SIZE + 1]
	char *tmp[BUFF_SIZE + 1]
	char *point;
	static char *postline;

	*buffer = '\0';
	while (rdd = read(fd, tmp, BUFF_SIZE) > 0 && !(point = ft_strchr(tmp, '\n')))
	{
		tmp[rdd] = '\0';
		buffer = ft_strjoin(buffer, tmp);
		strncpy(postline, point, rdd);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int fd;
	char **line;

	line = malloc(2);
	*line = malloc(10000);
	strcpy (*line, "ok!");
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		get_next_line(fd, line);
	}
	printf("%s\n", *line);
	return (0);
}
