/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpostada <jpostada@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:30:27 by jpostada          #+#    #+#             */
/*   Updated: 2024/04/02 18:39:18 by jpostada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "get_next_line.h"

void	free_ptr(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	set_content(int fd, char **content)
{
	char		*buffer;
	char		*tmp;
	ssize_t		bytes_read;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (free_ptr(content));
	buffer[BUFFER_SIZE] = '\0';
	while (!ft_strchr(*content, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_ptr(content), free(buffer), free(tmp));
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			return (free(buffer));
		tmp = ft_strjoin(*content, buffer);
		if (!tmp)
			return (free(buffer), free_ptr(content));
		*content = tmp;
	}
	free(buffer);
}

char	*extract_line(char *content)
{
	char	*nl_pos;
	char	*line;

	nl_pos = ft_strchr(content, '\n');
	if (!nl_pos)
	{
		line = ft_strdup(content);
		if (!line)
			return (NULL);
		return (line);
	}
	line = ft_substr(content, 0, nl_pos - content + 1);
	if (!line)
		return (NULL);
	return (line);
}

void	refresh_content(char **content)
{
	char	*nl_pos;
	char	*tmp;

	nl_pos = ft_strchr(*content, '\n');
	if (!nl_pos || ft_strlen(nl_pos + 1) == 0)
		return (free_ptr(content));
	tmp = ft_strdup(nl_pos + 1);
	if (!tmp)
		return (free_ptr(content));
	free_ptr(content);
	*content = tmp;
}

char	*get_next_line(int fd)
{
	static char	*content;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
	{
		free_ptr(&content);
		return (NULL);
	}
	line = NULL;
	set_content(fd, &content);
	if (!content)
		return (NULL);
	line = extract_line(content);
	if (!line)
	{
		free_ptr(&content);
		return (NULL);
	}
	refresh_content(&content);
	return (line);
}
