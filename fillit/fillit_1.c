//#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 550

int		g_coun;

void	epic_fail(int fd)
{
	write(1, "error\n", 6);
	close(fd);
	exit(EXIT_FAILURE);
}

int		count_squares_len(char *buff, int i, int symb, int n)
{	
	int		len;

	len = 0;
	while (buff[i] != '\0' && buff[0] != '\n')
	{
		if (buff[i] == '.' || buff[i] == '#')
			symb++;
		if (buff[i] == '\n')
		{
			if (buff[i - 1] == '.' || buff[i - 1] == '#')
				n++;
			if (n == 4)
			{
				//printf("count_squares symb%d\n", symb);
				if (symb != 16)
					return (0);
				len++;
				symb = 0;
				n = 0;
			}
		}
		i++;
	}
	return (len);
}

int		count_squares(char *buff)
{
	int		symb;
	int		len;
	int		n;
	int		i;

	i = 0;
	symb = 0;
	n = 0;
	len = count_squares_len(buff, i, symb, n);
	//printf("count_squares %d\n", len);
	while (buff[i] != '\0')
	{		
		if (buff[i] == '\n')
			n++;
		if (buff[i] != '\n')
			n = 0;
		if (n > 2)
			return (0);
		i++;		
	}
	//printf("n %d\n", n);
	if (len > 1 && len <= 26)
		return (len);
	return (0);
}

int		compare_gates(char *b, int i)
{
	//printf("compare_gates\n");
	if (b[i] == '#')
	{
		if (b[i + 1] == '#' || b[i - 1] == '#' || b[i + 5] == '#' || b[i - 5] == '#')
			return (1);
	}
	return (0);
}

int		check_garbage(char *buff)
{
	//printf("\ncheck_garbage\n");
	int		valid;
	int		i;
	int		n;

	valid = 0;
	i = -1;
	n = 0;
	while (buff[++i] != '\0')
	{
		if (buff[i] != '.' && buff[i] != '#' && buff[i] != '\n')
		{
			//printf("check_garbage %c %d\n", buff[i], i);
			return (0);
		}
		if (buff[i] == '#')
		{			
			if (compare_gates(buff, i))
			{	
				valid++;
				//printf("check_garbage compare_gate %d\n", valid);
			}		
			//else			
			//	return (0);
		}
		if (buff[i] == '\n')
		{
			if (buff[i - 1] == '.' || buff[i - 1] == '#')
				n++;
		}
		////printf("n %d\n", n);
		if (n == 4)
		{			
			if (valid != 4)
			{
				//printf("not valid %d\n", valid);
				return (0);
			}
			n = 0;
			valid = 0;
		}
	}
	//printf("check_garbage %d\n", valid);
	return (1);
}

void	errase_quad(char **quad)
{
	//printf("errase_quad\n");
	int		i;
	int		ln;

	i = -1;
	ln = 0;
	while (quad[++i] != '\0')
		ln++;
	//printf("errase %d\n", ln);
	i = 0;
	while (i < ln)
	{
		free(quad[i]);
		i++;
	}
	free(quad);
	quad = NULL;
	//printf("errase_quad ok\n");
}

char	**map_assembler(char *buff, int fd)
{
	int		ln;
	int		i;
	char	**map;

	//printf("map_assembler\n");	
	ln = count_squares(buff);
	//printf("ln %d\n", ln);
	i = 0;
	if(!(map = (char **)malloc(sizeof(char *) * (ln + 1))))
		return (NULL);
	while (i < ln)
	{
		if(!(map[i] = (char *)malloc(sizeof(char) * 17)))
		{
			errase_quad(map);
			return (NULL);
		}
		map[i][16] = '\0';
		i++;
	}
	map[ln] = NULL;
	//printf("map_assembler ok\n");
	return (map);
}

char	**map_builder(char **map, char *buff)
{
	int		i;
	int		j;
	int		k;
	int		count;
	
	//printf("map_builder\n");
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
	//printf("map_builder ok\n");
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
	//printf("find_ln %d\n", i);
	return (i);
}

int		find_sqrt(int ln)
{
	int		i;
	int		nbr;

	i = 2;
	nbr = ln * 4;
	while (i * i < nbr)
		i++;
	//printf("find_sqrt %d\n", i);
	return (i);
}

char 	**build_quad(int ln)
{
	int		i;
	int		j;
	char 	**quad;

	//printf("build_quad\n");
	//printf("build_quad ln %d\n", ln);
	i = 0;
	j = 0;
	quad = (char **)malloc(sizeof(char *) * ln + 1);
	if (!quad)
		return (NULL);
	while (i < ln)
	{
		if (!(quad[i] = (char *)malloc(sizeof(char) * 17)))
		{
			errase_quad(quad);
			return (NULL);
		}
		quad[i][16] = '\0';
		i++;
	}
	quad[i] = NULL;
	i = 0;
	while (i < ln)
	{
		while (j < ln)
		{
			quad[i][j++] = '.';
		}
		j = 0;
		i++;
	}
	return (quad);
}

void	printresult(char **quad)
{
	int		i;

	i = 0;
	//printf("printresult\n");
	while (quad[i])
	{
		printf("%s\n", quad[i]);
		i++;
	}
	errase_quad(quad);
}


/*int		map_length(char **quad)
{
	printf("map_length\n");
	int		i;

	i = 0;
	while (quad[i])
		i++;
	return (i);
}*/

char 	**write_tetris(char **quad, char *str, int y, int x)
{
	//printf("write_tetris\n");
	int		i;
	unsigned int	point;
	unsigned int	dot;
	//int		delim;

	i = 0;
	while (str[i] == '.')
		i++;
	dot = i;
	point = dot;
	//printf("write_tetris y %d x %d dot %d str %s\n", y, x, dot, str);
	while (str[point] != '\0')
	{
		if (str[point] != '.')
			quad[(y + (point >> 2)) - (dot >> 2)][(x + (point & 3)) - (dot & 3)] = str[point];
		point++;
	}
	return (quad);
}

//int		tet_len(char **quad)

int		read_tetrimin(char **quad, char *str, int y, int x)
{
	//printf("read_tetrimin\n");
	int		i;
	int		ln;
	unsigned int	point;
	unsigned int	dot;
	//int		delim;

	i = 0;
	while (str[i] == '.')
		i++;
	dot = i;
	point = dot;
	i = 0;
	while (quad[i])
		i++;
	ln = i;
	//printf("read_tetrimin y %d x %d dot %d ln %d str %s\n", y, x, dot, ln, str);
	while (str[point] != '\0')
	{
		if (str[point] != '.')
		{
			//printf("o Y %d X %d point %d dot %d\n", ((y + (point >> 2)) - (dot >> 2)), (x + (point % 4)) - dot % 4, point, dot);

			if ((y + (point >> 2) - (dot >> 2) >= ln)
				|| (x + (point & 3) - (dot & 3) >= ln)
				|| quad[(y + (point >> 2)) - (dot >> 2)]
				[(x + (point & 3)) - (dot & 3)] != '.')
				return (0);
		}
		point++;
	}
	return (1);
}
/*
read_tetrimin y 0 x 0 dot 4 ln 4 str ....AA...A...A..
o Y 0 X 0 point 4 dot 4
o Y 0 X 1 point 5 dot 4
o Y 1 X 1 point 9 dot 4
o Y 2 X 1 point 13 dot 4
*/
void	clear_item(char **quad, char *str)
{
	int		y;
	int		x;
	char 	c;

	y = 0;
	x = 0;
	while (*str == '.')
		str++;
	c = *str;
	//printf("clear_item %c\n", c);
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
	//printf("TETRIS %d\n", g_coun);
	int		y;
	int		x;
	char 	*str;

	y = 0;
	x = 0;
	g_coun++;
	if (!map[i])
		return (0);

	
	str = map[i];	
	//printf("tetris %d\n");

	/*int	k;
	k = 0;
	while (quad[k])
	{
		printf("%s\n", quad[k]);
		k++;
	}*/

	while (y < ln)
	{
		while (x < ln)
		{
			//printf("tetris Y, X %d %d\n", y, x);
			if (read_tetrimin(quad, str, y, x))
			{
				quad = write_tetris(quad, str, y, x);
				if ((tetris(quad, map, ln, i + 1)) == 0)
					return (0);
				//printf("tetris clear_item %s\n", str);
				clear_item(quad, str);
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
	//printf("\nconstructor\n");

	int		i;
	int		ln;
	char 	**quad;

	i = 0;
	map = letter_converter(map);

	/*while (map[i])
	{
			printf("%s\n", map[i]);
		i++;
	}*/

	ln = find_ln(map);
	quad = build_quad(find_sqrt(ln));
	i = 0;
	/*while (quad[i])
	{
			printf("%s\n", quad[i]);
		i++;
	}*/



	i = 0;
	while (tetris(quad, map, ln, i))//
	{
		//printf("%d\n", ln);
		errase_quad(quad);
		//system("leaks a.out");
		ln++;	
		quad = build_quad(find_sqrt(ln));
		//printf("construcor new %d\n", ln);
	}
	//printf("constructor ok\n");
	//printf("%d\n", 7/4);
	printresult(quad);
}

int		main(int argc, char **argv)
{
	int		i;
	int		fd;
	int		rd;
	char	*buff;
	char	**map;

	g_coun = 0;

	i = 0;
	if(argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if(!(buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
			return (0);
		rd = read(fd, buff, BUFFER_SIZE + 1);
		buff[rd] = '\0';
		if (!count_squares(buff) || !check_garbage(buff))
			epic_fail(fd);
		map = map_assembler(buff, fd);
		map = map_builder(map, buff);
		/*printf("map_builder result\n");
		while (map[i])
		{
				printf("%s\n", map[i]);
			i++;
		}*/
		constructor(map);
	}
	return (0);
}
