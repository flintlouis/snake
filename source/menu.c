/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 14:30:28 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/24 19:25:43 by fhignett      ########   odam.nl         */
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
				colour = (t_colour){(GAME->r - 20), (GAME->g - 20), (GAME->b - 20)};
			else
				colour = (t_colour){GAME->r, GAME->g, GAME->b};
			put_square(mlx, (t_point){x, y}, colour);
			x += GRID;
		}
		y += GRID;
	}
}

void    menu_title(t_mlx *mlx)
{
	static int i;
	static int j;
	static int k;

	if (k == WIDTH)
		i = 0;
	if (k >= WIDTH || k == 0)
	{
		mlx_string_put(mlx->mlx, mlx->win, -345 + i, 38, 0x000000, "                          ____");
		mlx_string_put(mlx->mlx, mlx->win, -345 + i, 53, 0x000000, " ________________________/ o  \\___/");
		mlx_string_put(mlx->mlx, mlx->win, -345 + i, 68, 0x000000, "<_____________________________/   \\");
		i += 2;
	}
	if (i == WIDTH)
		j = 0;
	if (i >= WIDTH)
	{
		mlx_string_put(mlx->mlx, mlx->win, -345 + j, 38, 0x000000, "                          ____");
		mlx_string_put(mlx->mlx, mlx->win, -345 + j, 53, 0x000000, " ________________________/ o  \\___/");
		mlx_string_put(mlx->mlx, mlx->win, -345 + j, 68, 0x000000, "<_____________________________/   \\");
		j += 2;
	}
	if (j == WIDTH)
		k = 0;
	if (j >= WIDTH)
	{
		mlx_string_put(mlx->mlx, mlx->win, -345 + k, 38, 0x000000, "                          ____");
		mlx_string_put(mlx->mlx, mlx->win, -345 + k, 53, 0x000000, " ________________________/ o  \\___/");
		mlx_string_put(mlx->mlx, mlx->win, -345 + k, 68, 0x000000, "<_____________________________/   \\");
		k += 2;
	}
	mlx_string_put(mlx->mlx, mlx->win, 265, 10, 0x000000, "*~~~~~*");
	mlx_string_put(mlx->mlx, mlx->win, 265, 20, 0x000000, "*SNAKE*");
	mlx_string_put(mlx->mlx, mlx->win, 265, 30, 0x000000, "*~~~~~*");
	mlx_string_put(mlx->mlx, mlx->win, 150, 100, 0x000000, "1 PLAYER");
	mlx_string_put(mlx->mlx, mlx->win, 380, 100, 0x000000, "2 PLAYER");
	mlx_string_put(mlx->mlx, mlx->win, 255, 150, 0x000000, "CONTROLS:");
	mlx_string_put(mlx->mlx, mlx->win, 25, 190, 0x000000, "1 : map 1");
	mlx_string_put(mlx->mlx, mlx->win, 177, 190, 0x000000, "2 : map 2");
	mlx_string_put(mlx->mlx, mlx->win, 328, 190, 0x000000, "3 : map 3");
	mlx_string_put(mlx->mlx, mlx->win, 480, 190, 0x000000, "R : reset");
	mlx_string_put(mlx->mlx, mlx->win, 25, 225, 0x000000, "player 1 :");
	mlx_string_put(mlx->mlx, mlx->win, 25, 250, 0x000000, "up    : move up");
	mlx_string_put(mlx->mlx, mlx->win, 25, 275, 0x000000, "<-    : move left");
	mlx_string_put(mlx->mlx, mlx->win, 25, 300, 0x000000, "down  : move down");
	mlx_string_put(mlx->mlx, mlx->win, 25, 325, 0x000000, "->    : move right");
	mlx_string_put(mlx->mlx, mlx->win, 25, 350, 0x000000, "space : boost");
	mlx_string_put(mlx->mlx, mlx->win, 410, 225, 0x000000, "player 2 :");
	mlx_string_put(mlx->mlx, mlx->win, 410, 250, 0x000000, "W    : move up");
	mlx_string_put(mlx->mlx, mlx->win, 410, 275, 0x000000, "A    : move left");
	mlx_string_put(mlx->mlx, mlx->win, 410, 325, 0x000000, "S    : move down");
	mlx_string_put(mlx->mlx, mlx->win, 410, 300, 0x000000, "D    : move right");
	mlx_string_put(mlx->mlx, mlx->win, 410, 350, 0x000000, "ctrl : boost");
}
