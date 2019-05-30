/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyconf_mouse.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/06 11:45:51 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/30 21:05:52 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

int				mouse_move(int x, int y, t_mlx *mlx)
{
	int x_mod;
	int y_mod;

	if ((x >= 140 && x <= 235) && (y >= 90 && y <= 125))
		GAME->p1 = 1;
	else if ((x >= 365 && x <= 460) && (y >= 90 && y <= 125))
		GAME->p2 = 1;
	else
	{
		GAME->p1 = 0;
		GAME->p2 = 0;
	}
	x_mod = x % 10;
	y_mod = y % 10;
	GAME->mouse.x = x - x_mod;
	GAME->mouse.y = y - y_mod;
	return (0);
}

int				mouse_press(int button, int x, int y, t_mlx *mlx)
{
	if (!GAME->menu)
	{
		if (!GAME->ai)
		{
			if (button == L_MOUSE)
				turn_left(&(KEYCONF[0]->move));
			else if (button == R_MOUSE)
				turn_right(&(KEYCONF[0]->move));
		}
		else if (GAME->ai)
		{
			if (button == L_MOUSE)
			{
				APPLE->pos.x = GAME->mouse.x;
				APPLE->pos.y = GAME->mouse.y;
			}
		}

	}
	return (0);
}

int				mouse_release(int button, int x, int y, t_mlx *mlx)
{
	if (GAME->menu)
	{
		if (button == L_MOUSE)
		{
			if ((x >= 140 && x <= 235) && (y >= 90 && y <= 125))
			{
				GAME->players = 1;
				GAME->menu = 0;
				setup_game(mlx);
			}
			else if ((x >= 365 && x <= 460) && (y >= 90 && y <= 125))
			{
				GAME->players = 2;
				GAME->menu = 0;
				setup_game(mlx);
			}
		}
	}
	if (button == 3)
		GAME->follow = (GAME->follow + 1) % 2;
	return (0);
}
