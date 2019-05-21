/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 14:30:28 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/21 16:50:04 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

void	menu(t_mlx *mlx)
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
			if ((GAME->p1 && (x >= 140 && x <= 235) && (y >= 90 && y <= 125))
			|| (GAME->p2 && (x >= 365 && x <= 460) && (y >= 90 && y <= 125)))
				colour = (t_colour){0x50, 0x50, 0x50};
			else
				colour = (t_colour){0x69, 0x69, 0x69};
			put_square(mlx, (t_point){x, y}, colour);
			x += GRID;
		}
		y += GRID;
	}
}

void    menu_title(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, 265, 10, 0x000000, "*~~~~~*");
	mlx_string_put(mlx->mlx, mlx->win, 265, 20, 0x000000, "*SNAKE*");
	mlx_string_put(mlx->mlx, mlx->win, 265, 30, 0x000000, "*~~~~~*");
	mlx_string_put(mlx->mlx, mlx->win, 150, 100,0x000000, "1 PLAYER");
	mlx_string_put(mlx->mlx, mlx->win, 380, 100,0x000000, "2 PLAYER");
	mlx_string_put(mlx->mlx, mlx->win, 255, 150,0x000000, "CONTROLS:");
}
