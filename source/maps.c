/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maps.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/20 17:42:43 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/21 13:27:23 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

static void	map1(t_mlx *mlx)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_square(mlx, (t_point){x, y}, (t_colour){0x1a, 0x3a, 0x3a});
			x += GRID;
		}
		y += GRID;
	}
}

static void	map2(t_mlx *mlx)
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
			if (y == 0 || x == 0 || x == WIDTH - GRID || y == HEIGHT - GRID)
				colour = (t_colour){0x69, 0x69, 0x69};
			else
				colour = (t_colour){0x1a, 0x3a, 0x3a};
			put_square(mlx, (t_point){x, y}, colour);
			x += GRID;
		}
		y += GRID;
	}
}

static void	map3(t_mlx *mlx)
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
			if ((x == 0 && ((y >= 0 && y <= 140) || (y >= 240 && y <= HEIGHT))) ||
			(x == WIDTH - GRID && ((y >= 0 && y <= 140) || (y >= 240 && y <= HEIGHT)))
			|| (y == 0 && ((x >= 0 && x <= 240) || (x >= 340 && x <= WIDTH))) ||
			(y == HEIGHT - GRID && ((x >= 0 && x <= 240) || (x >= 340 && x <= WIDTH)))
			|| (x == 240 && ((y >= 140 && y <= 240))) || (x == 340 && ((y >= 140 && y <= 240))))
				colour = (t_colour){0x69, 0x69, 0x69};
			else
				colour = (t_colour){0x1a, 0x3a, 0x3a};
			put_square(mlx, (t_point){x, y}, colour);
			x += GRID;
		}
		y += GRID;
	}
}

void	background(t_mlx *mlx)
{
	if (GAME->map == KEY_1)
		map1(mlx);
	else if (GAME->map == KEY_2)
		map2(mlx);
	else
		map3(mlx);
}
