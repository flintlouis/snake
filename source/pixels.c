/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixels.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/08 16:05:12 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/09 19:55:38 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>
#include <time.h>

void		put_pixel(int x, int y, t_mlx *mlx, t_colour colour)
{
	int i;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * mlx->bits_per_pixel / 8) + (y * mlx->size_line);
		mlx->data_addr[i] = colour.b;
		i++;
		mlx->data_addr[i] = colour.g;
		i++;
		mlx->data_addr[i] = colour.r;
	}
}

void		put_square(t_mlx *mlx, t_point pixel, t_colour colour)
{
	int i;
	int j;

	i = 0;
	while (i < GRID)
	{
		j = 0;
		while (j < GRID)
		{
			put_pixel(pixel.x + j, pixel.y + i, mlx, colour);
			j++;
		}
		i++;
	}
}

t_point random_pixel(void)
{
	t_point pixel;
	int nb;

	nb = (rand() % WIDTH);
	while (nb % GRID != 0)
		nb++;
	pixel.x = nb;
	nb = (rand() % HEIGHT);
	while (nb % GRID != 0)
		nb++;
	pixel.y = nb;
	return (pixel);
}
