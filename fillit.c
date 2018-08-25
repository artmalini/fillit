/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 10:49:09 by gvynogra          #+#    #+#             */
/*   Updated: 2017/11/26 11:18:47 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	epic_fail(int fd)
{
	write(1, "error\n", 6);
	close(fd);
	exit(EXIT_FAILURE);
}

void	errase_quad(char **quad)
{
	int		i;
	int		ln;

	i = -1;
	ln = 0;
	while (quad[++i] != '\0')
		ln++;
	i = 0;
	while (i < ln)
	{
		free(quad[i]);
		i++;
	}
	free(quad);
}

int		find_sqrt(int ln)
{
	int		i;
	int		nbr;

	i = 2;
	nbr = ln * 4;
	while (i * i < nbr)
		i++;
	return (i);
}

void	draw_dots(char *buff, int n)
{
	int		j;

	j = 0;
	while (j < n)
	{
		buff[j] = '.';
		j++;
	}
}

char	**build_quad(int ln)
{
	int		i;
	char	**quad;

	i = 0;
	if (!(quad = (char **)malloc(sizeof(char *) * (ln + 1))))
		return (NULL);
	while (i < ln)
	{
		if (!(quad[i] = (char *)malloc(sizeof(char) * (ln + 1))))
		{
			errase_quad(quad);
			return (NULL);
		}
		quad[i][ln] = '\0';
		i++;
	}
	quad[i] = NULL;
	i = 0;
	while (i < ln)
	{
		draw_dots(quad[i], ln);
		i++;
	}
	return (quad);
}
