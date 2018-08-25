/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 11:14:15 by gvynogra          #+#    #+#             */
/*   Updated: 2017/11/26 11:20:05 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**map_assembler(char *buff)
{
	int		ln;
	int		i;
	char	**map;

	ln = count_squares(buff);
	i = 0;
	if (!(map = (char **)malloc(sizeof(char *) * (ln + 1))))
		return (NULL);
	while (i < ln)
	{
		if (!(map[i] = (char *)malloc(sizeof(char) * 17)))
		{
			errase_quad(map);
			return (NULL);
		}
		map[i][16] = '\0';
		i++;
	}
	map[ln] = NULL;
	return (map);
}

char	**map_builder(char **map, char *buff)
{
	int		i;
	int		j;
	int		k;
	int		count;

	i = 0;
	j = 0;
	k = -1;
	count = 0;
	while (buff[++k] != '\0')
	{
		if (buff[k] != '\n')
			map[i][j++] = buff[k];
		if (buff[k] == '\n')
		{
			count++;
			if (count == 5)
			{
				count = 0;
				i++;
				j = 0;
			}
		}
	}
	return (map);
}

char	**letter_converter(char **map)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 1;
	while (map[i])
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '#')
				map[i][j] = k + 64;
			j++;
		}
		j = 0;
		k++;
		i++;
	}
	return (map);
}

int		find_ln(char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j] != '\0')
			j++;
		j = 0;
		i++;
	}
	return (i);
}
