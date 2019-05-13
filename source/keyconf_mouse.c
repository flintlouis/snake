/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyconf_mouse.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/06 11:45:51 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/13 22:54:30 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

int				mouse_move(int x, int y, t_mlx *mlx)
{
	return (0);
}

int				mouse_press(int button, int x, int y, t_mlx *mlx)
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
	
	return (0);
}

int				mouse_release(int button, int x, int y, t_mlx *mlx)
{
	return (0);
}
