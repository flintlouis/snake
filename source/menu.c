/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 14:30:28 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/21 15:34:09 by fhignett      ########   odam.nl         */
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
			if ((GAME->p1 && (x >= 140 && x <= 235) && (y >= 90 && y <= 125)) || (GAME->p2 && (x >= 365 && x <= 460) && (y >= 90 && y <= 125)))
				colour = (t_colour){0xFF, 0xDD, 0x33};
			else
				colour = (t_colour){0xD6, 0xB8, 0x24};
			put_square(mlx, (t_point){x, y}, colour);
			x += GRID;
		}
		y += GRID;
	}
}

void    menu_title(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, 265, 10, 255, "*~~~~~*");
	mlx_string_put(mlx->mlx, mlx->win, 265, 20, 255, "*SNAKE*");
	mlx_string_put(mlx->mlx, mlx->win, 265, 30, 255, "*~~~~~*");
	mlx_string_put(mlx->mlx, mlx->win, 150, 100, 255, "1 PLAYER");
	mlx_string_put(mlx->mlx, mlx->win, 380, 100, 255, "2 PLAYER");
	mlx_string_put(mlx->mlx, mlx->win, 255, 150, 255, "CONTROLS:");
}
