/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpostada <jpostada@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:30:48 by jpostada          #+#    #+#             */
/*   Updated: 2024/03/27 12:32:26 by jpostada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
int		ft_strlen(char *string);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *string, int chrstr);
#endif
