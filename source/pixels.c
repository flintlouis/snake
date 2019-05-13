/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixels.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/08 16:05:12 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/13 17:41:54 by fhignett      ########   odam.nl         */
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

t_point		random_pixel(void)
{
	t_point pixel;
	int nb;

	nb = (rand() % WIDTH - GRID);
	while (nb % GRID != 0)
		nb++;
	if (nb == WIDTH - GRID)
		nb -= GRID;
	else if (nb == 0)
		nb += GRID;
	pixel.x = nb;
	nb = (rand() % HEIGHT - GRID);
	while (nb % GRID != 0)
		nb++;
	if (nb == HEIGHT - GRID)
		nb -= GRID;
	else if (nb == 0)
		nb += GRID;
	pixel.y = nb;
	return (pixel);
}

void	background(t_mlx *mlx)
{
	int x;
	int y;
	t_colour colour;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// if (y == 0 || x == 0 || x == WIDTH - GRID || y == HEIGHT - GRID) /* COMMENT OUT FOR NO SIDE COLOUR */
			// 	colour = (t_colour){0x69, 0x69, 0x69};
			// else
				colour = (t_colour){0x1a, 0x3a, 0x3a};
			put_square(mlx, (t_point){x, y}, colour);
			x += GRID;
		}
		y += GRID;
	}
}
