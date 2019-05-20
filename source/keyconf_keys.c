/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyconf_keys.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 14:18:18 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/20 18:48:12 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

int			close_window(void *ptr)
{
	(void)ptr;
	exit(0);
	return (0);
}

static void	delete_snake(t_snake *snake)
{
	if (!snake)
		return ;
	delete_snake(snake->next);
	free(snake);
	snake = NULL;
}

static	void game_reset(t_mlx *mlx)
{
	int i;
	int player;

	i = 0;
	player = 0;
	while (player < mlx->players)
	{
		delete_snake(SNAKEHEAD[player]);
		free(KEYCONF[player]);
		KEYCONF[player] = NULL;
		player++;
	}
	free(SNAKEHEAD);
	free(KEYCONF);
	init_keyconf(mlx);
	init_snake(mlx);
	APPLE->on = 0;
	mlx->game_over = 0;
	system("clear");
}

int			release_key(int key, t_mlx *mlx)
{
	if (key == KEY_SPACE)
		game_reset(mlx);
	if (key == KEY_1)
	{
		mlx->map = KEY_1;
		game_reset(mlx);
	}
	else if (key == KEY_2)
	{
		mlx->map = KEY_2;
		game_reset(mlx);
	}
	else if (key == KEY_3)
	{
		mlx->map = KEY_3;
		game_reset(mlx);
	}
	if (key == KEY_RSHIFT)
	{
		KEYCONF[0]->speed += 50;
		KEYCONF[0]->nitro = 0;
	}
	if (mlx->players == 2 && key == KEY_LSHIFT)
	{
		KEYCONF[1]->speed += 50;
		KEYCONF[1]->nitro = 0;
	}
	return (0);
}

static void	update_movement(int key, t_mlx *mlx, int player)
{
	if (KEYCONF[player]->updated)
	{
		KEYCONF[player]->move = key;
		KEYCONF[player]->updated = 0;
	}
}

int			press_key(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		close_window(NULL);
	if (key == KEY_PLUS && KEYCONF[0]->speed > 18)
		KEYCONF[0]->speed -= 2;
	if (key == KEY_MIN)
		KEYCONF[0]->speed += 2;
	/* MOVEMENT PLAYER 1 */
	if (key == KEY_RIGHT && KEYCONF[0]->move != KEY_LEFT)
		update_movement(KEY_RIGHT, mlx, 0);
	else if (key == KEY_LEFT && KEYCONF[0]->move != KEY_RIGHT)
		update_movement(KEY_LEFT, mlx, 0);
	else if (key == KEY_UP && KEYCONF[0]->move != KEY_DOWN)
		update_movement(KEY_UP, mlx, 0);
	else if (key == KEY_DOWN && KEYCONF[0]->move != KEY_UP)
		update_movement(KEY_DOWN, mlx, 0);
	/* MOVEMENT PLAYER 2 */
	if (mlx->players == 2)
	{
		if (key == KEY_RSHIFT && KEYCONF[0]->nitro != 1)
		{
			KEYCONF[0]->speed -= 50;
			KEYCONF[0]->nitro = 1;
		}
		if (key == KEY_D && KEYCONF[1]->move != KEY_A)
			update_movement(KEY_D, mlx, 1);
		else if (key == KEY_A && KEYCONF[1]->move != KEY_D)
			update_movement(KEY_A, mlx, 1);
		else if (key == KEY_W && KEYCONF[1]->move != KEY_S)
			update_movement(KEY_W, mlx, 1);
		else if (key == KEY_S && KEYCONF[1]->move != KEY_W)
			update_movement(KEY_S, mlx, 1);
		if (key == KEY_LSHIFT && KEYCONF[1]->nitro != 1)
		{
			KEYCONF[1]->speed -= 50;
			KEYCONF[1]->nitro = 1;
		}
	}
	// printf("%d\n", key);
	return (0);
}
