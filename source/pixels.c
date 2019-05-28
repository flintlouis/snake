/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixels.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/08 16:05:12 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/28 18:57:18 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>
#include <time.h>

static void		put_pixel(int x, int y, t_mlx *mlx, t_colour colour)
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

void			put_square(t_mlx *mlx, t_point pixel, t_colour colour)
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

t_point			random_pixel(void)
{
	t_point pixel;
	int		nb;

	nb = (rand() % (WIDTH - GRID));
	while (nb % GRID != 0)
		nb++;
	if (nb == WIDTH - GRID)
		nb -= GRID;
	else if (nb == 0)
		nb += GRID;
	pixel.x = nb;
	nb = (rand() % (HEIGHT - GRID));
	while (nb % GRID != 0)
		nb++;
	if (nb == HEIGHT - GRID)
		nb -= GRID;
	else if (nb == 0)
		nb += GRID;
	pixel.y = nb;
	return (pixel);
}
