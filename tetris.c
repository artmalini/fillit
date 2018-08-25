/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 11:10:52 by gvynogra          #+#    #+#             */
/*   Updated: 2017/11/26 11:21:16 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	write_tetris(char **quad, char *str, int y, int x)
{
	int				i;
	unsigned int	point;
	unsigned int	dot;

	i = 0;
	while (str[i] == '.')
		i++;
	dot = i;
	point = dot;
	while (str[point] != '\0')
	{
		if (str[point] != '.')
			quad[ycord(y, point, dot)][xcord(x, point, dot)] = str[point];
		point++;
	}
}

int		read_tetrimin(char **quad, char *str, int y, int x)
{
	int				i;
	unsigned int	point;
	unsigned int	dot;

	i = 0;
	while (str[i] == '.')
		i++;
	dot = i;
	point = dot;
	i = 0;
	while (quad[i])
		i++;
	while (str[point] != '\0')
	{
		if (str[point] != '.')
		{
			if ((ycord(y, point, dot) >= i) || (xcord(x, point, dot) >= i))
				return (0);
			if (quad[ycord(y, point, dot)][xcord(x, point, dot)] != '.')
				return (0);
		}
		point++;
	}
	write_tetris(quad, str, y, x);
	return (1);
}

void	clear_item(char **quad, char *str)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	x = 0;
	while (*str == '.')
		str++;
	c = *str;
	while (quad[y])
	{
		while (quad[y][x] != '\0')
		{
			if (quad[y][x] == c)
				quad[y][x] = '.';
			x++;
		}
		x = 0;
		y++;
	}
}

int		tetris(char **quad, char **map, int ln, int i)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	if (!map[i])
		return (0);
	while (y < ln)
	{
		while (x < ln)
		{
			if (read_tetrimin(quad, map[i], y, x))
			{
				if ((tetris(quad, map, ln, i + 1)) == 0)
					return (0);
				clear_item(quad, map[i]);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

void	constructor(char **map)
{
	int		i;
	int		ln;
	char	**quad;

	i = 0;
	map = letter_converter(map);
	ln = find_ln(map);
	quad = build_quad(find_sqrt(ln));
	i = 0;
	while (tetris(quad, map, find_sqrt(ln), i))
	{
		errase_quad(quad);
		ln++;
		quad = build_quad(find_sqrt(ln));
	}
	printresult(quad);
}
