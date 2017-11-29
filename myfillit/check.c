/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 11:04:48 by gvynogra          #+#    #+#             */
/*   Updated: 2017/11/26 11:05:05 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		count_squares_len(char *buff, int i, int symb, int n)
{
	int		len;

	len = 0;
	while (buff[++i] != '\0' && buff[0] != '\n')
	{
		if (buff[i] == '.' || buff[i] == '#')
			symb++;
		if (buff[i] == '\n')
		{
			if (buff[i - 1] == '.' || buff[i - 1] == '#')
				n++;
			if (n == 4)
			{
				if ((symb == 16 && (buff[i + 1] == '.' || buff[i + 1] == '#'))
				|| symb != 16)
					return (0);
				len++;
				symb = 0;
				n = 0;
			}
		}
	}
	if (symb != 0)
		return (0);
	return (len);
}

int		count_squares(char *buff)
{
	int		symb;
	int		len;
	int		n;
	int		i;

	i = -1;
	symb = 0;
	n = 0;
	len = count_squares_len(buff, i, symb, n);
	while (buff[++i] != '\0')
	{
		if (buff[i] == '\n')
			n++;
		if (buff[i] != '\n')
			n = 0;
		if (n > 2)
			return (0);
	}
	if (n != 1)
		return (0);
	if (len >= 1 && len <= 26)
		return (len);
	return (0);
}

int		check_garbage(char *buff)
{
	int		i;

	i = -1;
	while (buff[++i] != '\0')
	{
		if (buff[i] != '.' && buff[i] != '#' && buff[i] != '\n')
			return (0);
	}
	return (1);
}

int		checkstr(char *str)
{
	int		j;
	int		count;

	j = 0;
	count = 0;
	while (j < 16)
	{
		if (str[j] == '#')
		{
			if (str[j + 1] == '#')
				count++;
			if (str[j - 1] == '#')
				count++;
			if (str[j + 4] == '#')
				count++;
			if (str[j - 4] == '#')
				count++;
		}
		j++;
	}
	return (count);
}

int		check(char **map, int len)
{
	int		k;
	int		j;

	j = 0;
	k = 0;
	while (j < len)
	{
		k = checkstr(map[j]);
		if (k != 8 && k != 6)
			return (0);
		j++;
	}
	return (1);
}
