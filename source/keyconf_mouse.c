/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyconf_mouse.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/06 11:45:51 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/21 16:08:00 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

int				mouse_move(int x, int y, t_mlx *mlx)
{
	if ((x >= 140 && x <= 235) && (y >= 90 && y <= 125))
		GAME->p1 = 1;
	else if ((x >= 365 && x <= 460) && (y >= 90 && y <= 125))
		GAME->p2 = 1;
	else
	{
		GAME->p1 = 0;
		GAME->p2 = 0;
	}
	return (0);
}

int				mouse_press(int button, int x, int y, t_mlx *mlx)
{
	if (!GAME->menu)
	{
		if (button == L_MOUSE)
		{
			if (KEYCONF[0]->move == KEY_RIGHT)
				KEYCONF[0]->move = KEY_UP;
			else if (KEYCONF[0]->move == KEY_UP)
				KEYCONF[0]->move = KEY_LEFT;
			else if (KEYCONF[0]->move == KEY_LEFT)
				KEYCONF[0]->move = KEY_DOWN;
			else if (KEYCONF[0]->move == KEY_DOWN)
				KEYCONF[0]->move = KEY_RIGHT;
		}
		else if (button == R_MOUSE)
		{
			if (KEYCONF[0]->move == KEY_RIGHT)
				KEYCONF[0]->move = KEY_DOWN;
			else if (KEYCONF[0]->move == KEY_DOWN)
				KEYCONF[0]->move = KEY_LEFT;
			else if (KEYCONF[0]->move == KEY_LEFT)
				KEYCONF[0]->move = KEY_UP;
			else if (KEYCONF[0]->move == KEY_UP)
				KEYCONF[0]->move = KEY_RIGHT;
		}
	}
	return (0);
}

int				mouse_release(int button, int x, int y, t_mlx *mlx)
{
	if (button == L_MOUSE)
	{
		if ((x >= 140 && x <= 235) && (y >= 90 && y <= 125))
		{
			GAME->players = 1;
			GAME->menu = 0;
			init_keyconf(mlx);
			init_snake(mlx);
		}
		else if ((x >= 365 && x <= 460) && (y >= 90 && y <= 125))
		{
			GAME->players = 2;
			GAME->menu = 0;
			init_keyconf(mlx);
			init_snake(mlx);
		}
	}
	return (0);
}
