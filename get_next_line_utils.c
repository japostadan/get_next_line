/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpostada <jpostada@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:31:04 by jpostada          #+#    #+#             */
/*   Updated: 2024/03/27 11:25:34 by jpostada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;
	size_t	k;

	k = ft_strlen(s1);
	i = 0;
	j = 0;
	ptr = malloc(sizeof(char) * (k + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1 && i < k)
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2 && i < k + ft_strlen(s2))
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}

char	*ft_strchr(char *string, int chrstr)
{
	int		i;
	int		j;
	char	*save;

	i = 0;
	j = 0;
	while (string[i] != (char)chrstr)
	{
		if (string[i] == '\0')
			return (0);
		i++;
	}
	if (!string[i] || (string[i] == chrstr && string[i + 1] == '\0'))
		return (NULL);
	save = malloc (sizeof(char) * ((ft_strlen(string) - i) + 1));
	if (!save)
		return (NULL);
	i++;
	while (i < ft_strlen(string))
		save[j++] = string[i++];
	save[j] = '\0';
	return (save);
}
