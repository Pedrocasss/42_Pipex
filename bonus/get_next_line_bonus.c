/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:12:35 by psoares-          #+#    #+#             */
/*   Updated: 2023/09/22 10:53:33 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static size_t	ft_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

static int	ft_limpamemo(char *buff)
{
	int	i;
	int	is_nline;
	int	j;

	i = 0;
	j = 0;
	is_nline = 0;
	while (buff[i])
	{
		if (is_nline)
			buff[j++] = buff[i];
		if (buff[i] == '\n')
			is_nline = 1;
		buff[i++] = '\0';
	}
	return (is_nline);
}

static char	*ft_join(char *str1, char *str2)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = malloc(ft_len(str1) + ft_len(str2) + 1);
	if (!newstr)
		return (NULL);
	while (str1 && str1[i])
	{
		newstr[i] = str1[i];
		i++;
	}
	free(str1);
	while (*str2)
	{
		newstr[i++] = *str2;
		if (*str2++ == '\n')
			break ;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	buff[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			i;

	i = 0;
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0 || fd >= FOPEN_MAX)
	{
		while (fd >= 0 && fd <= FOPEN_MAX && buff[fd][i])
			buff[fd][i++] = 0;
		return (NULL);
	}
	line = NULL;
	while ((buff[fd][0] || read(fd, buff[fd], BUFFER_SIZE) > 0))
	{
		line = ft_join(line, buff[fd]);
		if (ft_limpamemo(buff[fd]))
			break ;
	}
	return (line);
}
