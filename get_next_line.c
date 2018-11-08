/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:00:19 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/08 21:01:04 by qbackaer         ###   ########.fr       */
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
		ln_buff = ft_strjoin(ln_buff, rd_buff);
		ft_bzero(rd_buff, ft_strlen(rd_buff) + 1);
	}
	if (ret > 0)
		ln_buff = ft_strjoin(ln_buff, rd_buff);
	ft_bzero(rd_buff, ft_strlen(rd_buff) + 1);
	if ((chr = ft_strchr(ln_buff, SPR)))
	{
		if (ret > 1)
			*leftover = ft_strdup(chr + 1);
		*chr = '\0';
	}
	return (ln_buff);
}

int		get_next_line(const int fd, char **line)
{
	char		*buffer;
	static char	*leftover;
	char		*lo_chr;

	buffer = NULL;
	if (fd < 0 || !line || BUFF_SIZE < 1 || read (fd,buffer,0) ==  -1)
		return (-1);
	buffer = ft_strnew(0);
	if (leftover)
	{
		buffer = ft_strjoin(buffer, leftover);
		if ((lo_chr = ft_strchr(buffer, SPR)))
		{
			leftover = ft_strdup(lo_chr + 1);
			*lo_chr = '\0';
			*line = buffer;
			return (1);
		}
		else
			free(leftover);
	}
	buffer = ft_strjoin(buffer, read_until(fd, &leftover));
	*line = buffer;
	if (!ft_strlen(*line))
		return (0);
	return (1);
}
