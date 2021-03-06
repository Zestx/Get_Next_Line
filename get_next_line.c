/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:00:19 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/22 20:01:55 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until(const int fd, char **leftover)
{
	char	*rd_buff;
	char	*ln_buff;
	size_t	ret;
	char	*chr;

	rd_buff = ft_strnew(BUFF_SIZE);
	ln_buff = ft_strnew(0);
	chr = NULL;
	while ((ret = read(fd, rd_buff, BUFF_SIZE)) > 0 && !ft_strchr(rd_buff, SPR))
	{
		rd_buff[ret] = '\0';
		chr = ft_strjoin(ln_buff, rd_buff); //(LEAK) & check if null
		free(ln_buff);
		ln_buff = chr;
		ft_bzero(rd_buff, ft_strlen(rd_buff)); //?
	}
	if (ret > 0)
	{
		chr = ft_strjoin(ln_buff, rd_buff); //(LEAK) & check if null
		free(ln_buff);
		ln_buff = chr;
	}
	ft_bzero(rd_buff, ft_strlen(rd_buff));
	if ((chr = ft_strchr(ln_buff, SPR)))
	{
		if (ret > 1)
			*leftover = ft_strdup(chr + 1);
		*chr = '\0';
	}
	free(rd_buff);
	return (ln_buff);
}

int		get_next_line(const int fd, char **line)
{
	static char	*leftover[1000];
	char		*chr;

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, *line, 0) == -1)
		return (-1);
	*line = ft_strnew(0); //check if null
	if (leftover[fd])
	{
		chr = ft_strjoin(*line, leftover[fd]);
		free(*line);
		*line = chr;
		if ((chr = ft_strchr(*line, SPR)))
		{
			leftover[fd] = ft_strdup(chr + 1);
			*chr = '\0';
			return (1);
		}
	}
	*line = ft_strjoin(*line, read_until(fd, &leftover[fd]));
	if (!ft_strlen(*line))
	{
		if (leftover[fd])
			free(leftover[fd]);
		return (0);
	}
	return (1);
}
