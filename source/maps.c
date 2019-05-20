/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maps.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/20 17:42:43 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/20 23:07:16 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

static void	map_1(t_mlx *mlx)
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

static void	map_2(t_mlx *mlx)
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

static void	map_3(t_mlx *mlx)
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
			if ((y >= 140 && y <= 240) || (x >= 250 && x <= 350)
			|| ((x == 100 || x == 300) && (y >= 140 && y <= 240)))
				colour = (t_colour){0x00, 0x00, 0x00};
			else if (y == 0 || x == 0 || x == WIDTH - GRID || y == HEIGHT - GRID)
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
		map_1(mlx);
	else if (GAME->map == KEY_2)
		map_2(mlx);
	else
		map_3(mlx);
}
