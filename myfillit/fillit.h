/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:03:44 by amakhiny          #+#    #+#             */
/*   Updated: 2017/11/26 10:48:12 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include "libft.h"
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 546

void	epic_fail(int fd);
int		count_squares_len(char *buff, int i, int symb, int n);
int		count_squares(char *buff);
int		compare_gates(char *b, int i);
int		check_garbage(char *buff);
void	errase_quad(char **quad);
char	**map_assembler(char *buff);
char	**map_builder(char **map, char *buff);
char	**letter_converter(char **map);
int		find_ln(char **map);
int		find_sqrt(int ln);
void	draw_dots(char *buff, int n);
char	**build_quad(int ln);
void	printresult(char **quad);
char	**write_tetris(char **quad, char *str, int y, int x);
int		read_tetrimin(char **quad, char *str, int y, int x);
void	draw_dots(char *buff, int n);
void	clear_item(char **quad, char *str);
int		tetris(char **quad, char **map, int ln, int i);
void	constructor(char **map);
int		checkstr(char *str);
int		check(char **map, int i);
char	**parse_file(int fd);

#endif
