/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:27:00 by aouchaad          #+#    #+#             */
/*   Updated: 2022/11/22 19:15:54 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_for_nline(char *line)
{
	int	i;	

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_line_with_save(int fd, char *save)
{
	char	*buf;
	int		y;

	buf = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	while (1)
	{
		y = read(fd, buf, BUFFER_SIZE);
		if (y == 0)
			break ;
		if (y == -1)
		{
			free(save);
			free(buf);
			return (NULL);
		}
		buf[y] = '\0';
		save = ft_strjoin(save, buf);
		if (check_for_nline(save) == 1)
			break ;
	}
	free(buf);
	return (save);
}

char	*get_exact_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	line = malloc (sizeof(char) * (i + 2));
	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*linefree;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fd == 1 || fd == 2)
		return (NULL);
	save = get_line_with_save(fd, save);
	line = get_exact_line(save);
	if (!line)
		return (NULL);
	linefree = save;
	save = ft_strchr(linefree, '\n');
	free(linefree);
	return (line);
}
