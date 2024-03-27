/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qli <qli@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 14:48:19 by qli           #+#    #+#                 */
/*   Updated: 2020/11/06 15:11:21 by qli           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
/*
int		main(int argc, char **argv)
{
    int     fd;

    if (argc != 2)
    {
        printf("Please run \"./get_next_line file_name\"\n");
        return (1);
    }    
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (1);
    else
    {
        while (get_next_line(fd))
        {
            printf("%d",fd);
        }
    }
    close(fd);
    return (0);
}
*/

int main(void)
{
	char	*line;
	int	fd;
	
	fd = open("test.txt", O_RDONLY);
	line = (char *)1;

	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
