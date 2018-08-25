/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:22:35 by amakhiny          #+#    #+#             */
/*   Updated: 2017/12/04 12:22:42 by amakhiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ycord(int y, unsigned int point, unsigned int dot)
{
	return ((y + (point >> 2)) - (dot >> 2));
}

int		xcord(int x, unsigned int point, unsigned int dot)
{
	return ((x + (point & 3)) - (dot & 3));
}
