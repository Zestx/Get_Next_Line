/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 21:00:43 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/05 17:38:41 by qbackaer         ###   ########.fr       */
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
	char *tmp;

	if (!line || fd < 0)
		return (-1);
	if (!(tmp = malloc(BUFF_SIZE + 1)) || !(*line = malloc(BUFF_SIZE + 1)))
			return (-1);
	while (strchr(tmp, '\n'))
	{
		read(1, tmp, BUFF_SIZE);
	}
	strcpy(*line, tmp);
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
