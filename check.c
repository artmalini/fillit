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

int		compare_gates_valid(char *buff, int j, int k)
{
	int		count;
	int		hq;

	count = 0;
	hq = 0;
	while (++j < 20)
	{
		if (buff[k] == 35)
		{
			if (buff[k + 1] == 35 && (j + 1) < 20)
				count++;
			if (buff[k - 1] == 35 && (j - 1) >= 0)
				count++;
			if (buff[k + 5] == 35 && (j + 5) < 20)
				count++;
			if (buff[k - 5] == 35 && (j - 5) >= 0)
				count++;
			hq++;
		}
		k++;
	}
	if ((count != 6 && count != 8) || hq != 4)
		return (0);
	return (1);
}

int		compare_gates(char *buff)
{
	int		i;
	int		j;
	int		k;
	int		hq;

	i = 0;
	j = -1;
	k = 0;
	hq = 0;
	while (buff[i] != '\0')
	{
		if ((i % 21) == 0)
		{
			k = i;
			if (!compare_gates_valid(buff, j, k))
				return (0);
		}
		i++;
	}
	return (1);
}

int		check_garbage(char *buff)
{
	int		valid;
	int		i;

	valid = 0;
	i = -1;
	if (!compare_gates(buff))
		return (0);
	while (buff[++i] != '\0')
	{
		if (buff[i] != '.' && buff[i] != '#' && buff[i] != '\n')
			return (0);
	}
	return (1);
}
