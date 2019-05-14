/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyconf_keys.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 14:18:18 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/14 09:19:05 by FlintLouis    ########   odam.nl         */
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
	free(KEYCONF);
	init_keyconf(mlx);
	while (player < mlx->players)
	{
		delete_snake(SNAKEHEAD[player]);
		player++;
	}
	init_snake(mlx);
	APPLE->on = 0;
	system("clear");
}

int			release_key(int key, t_mlx *mlx)
{
	if (key == KEY_1)
		printf("apple.x : %d, apple.y : %d\n", mlx->apple->pos.x, mlx->apple->pos.y);
	if (key == KEY_SPACE)
		game_reset(mlx);
	if (key == KEY_SHIFT)
	{
		mlx->walls = (mlx->walls + 1) % 2;
		game_reset(mlx);
	}
	return (0);
}

int			press_key(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		close_window(NULL);
	if (key == KEY_PLUS && KEYCONF[0]->speed > 18)
	{
		KEYCONF[0]->speed -= 2;
		printf("\nspeed : %ld\n", KEYCONF[0]->speed);
		// add_snake_body(mlx, 0);
	}
	if (key == KEY_MIN)
	{
		KEYCONF[0]->speed += 2;
		printf("\nspeed : %ld\n", KEYCONF[0]->speed);

	}
	if (key == KEY_RIGHT && KEYCONF[0]->move != KEY_LEFT)
		KEYCONF[0]->move = KEY_RIGHT;
	else if (key == KEY_LEFT && KEYCONF[0]->move != KEY_RIGHT)
		KEYCONF[0]->move = KEY_LEFT;
	else if (key == KEY_UP && KEYCONF[0]->move != KEY_DOWN)
		KEYCONF[0]->move = KEY_UP;
	else if (key == KEY_DOWN && KEYCONF[0]->move != KEY_UP)
		KEYCONF[0]->move = KEY_DOWN;
	if (mlx->players == 2)
	{
		if (key == KEY_D && KEYCONF[1]->move != KEY_A)
			KEYCONF[1]->move = KEY_D;
		else if (key == KEY_A && KEYCONF[1]->move != KEY_D)
			KEYCONF[1]->move = KEY_A;
		else if (key == KEY_W && KEYCONF[1]->move != KEY_S)
			KEYCONF[1]->move = KEY_W;
		else if (key == KEY_S && KEYCONF[1]->move != KEY_W)
			KEYCONF[1]->move = KEY_S;
	}
	return (0);
}
