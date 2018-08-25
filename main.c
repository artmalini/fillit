/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 10:57:17 by gvynogra          #+#    #+#             */
/*   Updated: 2017/11/26 10:59:36 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	printresult(char **quad)
{
	int		i;

	i = 0;
	while (quad[i])
	{
		ft_putendl(quad[i]);
		i++;
	}
	errase_quad(quad);
}

char	**parse_file(int fd)
{
	char	*buff;
	char	**map;
	int		rd;

	if (!(buff = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		epic_fail(fd);
	rd = read(fd, buff, BUFF_SIZE + 1);
	buff[rd] = '\0';
	if (!count_squares(buff) || !check_garbage(buff))
		epic_fail(fd);
	map = map_assembler(buff);
	map = map_builder(map, buff);
	free(buff);
	return (map);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	**map;

	fd = 0;
	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			epic_fail(fd);
		map = parse_file(fd);
		constructor(map);
		close(fd);
	}
	else
	{
		ft_putendl("Usage: fillit <filename>");
		exit(1);
	}
	return (0);
}
