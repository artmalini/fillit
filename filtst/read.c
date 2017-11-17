/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 12:02:04 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/15 14:10:50 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

void	error(void)
{
	ft_putstr("error\n");
}

t_bool	valid_1(char *str, int bytes)
{
	int n;
	int i;
	int count1;
	int count2;

	n = 0;
	while (n < bytes)
	{
		i = -1;
		count1 = 0;
		count2 = 0;
		while (++i < 19)
		{
			if (str[n + i] == '#')
				count1++;
			if (str[n + i] == '.')
				count2++;
		}
		if (count1 != 4)
			return (false);
		if (count2 != 12)
			return (false);
		n += 21;
	}
	return (true);
}

t_bool	valid_2(char *str, int bytes)
{
	int n;
	int i;
	int k;

	n = 0;
	while (n < bytes)
	{
		i = 0;
		while (i <= 15)
		{
			k = n + i;
			if (!V1(str[k]) || !V1(str[k + 1]) || !V1(str[k + 2])
					|| !V1(str[k + 3]) || !V2(str[k + 4]))
				return (false);
			i += 5;
			printf("i %d\n", i);
			printf("k %d\n", k);
		}
		n += 21;
	}
	return (true);
}

t_bool	valid_0(char *str, int bytes)
{
	bytes++;
	if (str[0] != '.' && str[0] != '#')
		return (false);
	if (valid_1(str, bytes) == false)
		return (false);
	if (valid_2(str, bytes) == false)
		return (false);
	while (*str)
	{
		if (!V3(*str))
			return (false);
		str++;
	}
	return (true);
}

int		main(int av, char **ac)
{
	size_t	fd;
	size_t	rd;
	char	*str;
	char	**tbl;
	size_t	blocks;

	CHK1(av != 2, ft_putstr("usage: ./fillit source_file\n"), 0);
	CHK1((str = ft_strnew(BUFFER_SIZE)) == NULL, error(), 0);
	CHK2((fd = open(ac[1], O_RDONLY, S_IRUSR)) == -1, free(str), error(), 0);
	CHK3((rd = read(fd, str, BUFFER_SIZE)) < 0, error(), free(str),	 	 		//buffer size
															close(fd), 0);
	close(fd);
	CHK2(str[545] != 0, error(), free(str), 0);
	CHK2(!valid_0(str, rd), error(), free(str), 0);

	printf("rd %zu\n", rd);													//183	
	blocks = (rd + 1) / 21;													//8,76   9 после присвоения как и было в карте
	printf("blocks %zu\n", blocks);
	change_end(&str, rd);
	CHK2((tbl = ft_strsplit(str, '@')) == 0, error(), free(str), 0);

	trim_newline(tbl);													//квадрат 17х9 с паттернами   .....##..##.....   populate_valid
																		//							  ...#...#...#...#
	CHK3(!valid_pattern(tbl, blocks), error(), ft_tbldel(tbl), free(str), 0);
	rename_block(tbl);
	/*while (*tbl)
	{
		printf("%s\n", *tbl);
		tbl++;
	}*/
	solve(tbl, blocks);
	ft_tbldel(tbl);
	free(str);
	return (0);
}
