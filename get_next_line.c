/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megordag <megordag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 10:44:16 by mervegordag       #+#    #+#             */
/*   Updated: 2022/11/15 01:27:42 by megordag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_re(char *str)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!s)
		return (NULL);
	i++;
	c = 0;
	while (str[i])
		s[c++] = str[i++];
	s[c] = '\0';
	free(str);
	return (s);
}

char	*ft_read_save(int fd, char *m)
{
	int		byts;
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	byts = 1;
	while (!ft_strchr(m, '\n') && byts != 0)
	{
		byts = read (fd, buff, BUFFER_SIZE);
		if (byts == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byts] = '\0';
		m = ft_strjoin(m, buff);
	}
	free(buff);
	return (m);
}

char	*get_next_line(int fd)
{
	static char		*s;
	char			*buff;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	s = ft_read_save(fd, s);
	if (!s)
		return (NULL);
	buff = ft_line(s);
	s = ft_re(s);
	return (buff);
}
