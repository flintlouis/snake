/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/08 16:59:59 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/15 11:19:43 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <time.h>
#include <stdlib.h>

void init_snake(t_mlx *mlx)
{
	int i;
	int player;

	SNAKEHEAD = (t_snake**)malloc(sizeof(t_snake*) * (mlx->players + 1));
	player = 0;
	while (player < mlx->players)
	{
		i = 0;
		SNAKEHEAD[player] = MEM(t_snake);
		if (mlx->players == 1)
			SNAKEHEAD[player]->cur_pos = (t_point){WIDTH / 2, HEIGHT / 2 };
		else
			SNAKEHEAD[player]->cur_pos = (t_point){WIDTH / 4 + (WIDTH / 2 * player), HEIGHT / 2 };
		SNAKEHEAD[player]->old_pos = SNAKEHEAD[player]->cur_pos;
		while (i < 5)
		{
			add_snake_body(mlx, player);
			i++;
		}
		player++;
	}
	SNAKEHEAD[player] = NULL;
}

void init_keyconf(t_mlx *mlx)
{
	int player;

	player = 0;
	KEYCONF = (t_keyconf**)malloc(sizeof(t_keyconf*) * mlx->players);
	while (player < mlx->players)
	{
		KEYCONF[player] = MEM(t_keyconf);
		if (player == 0)
			KEYCONF[player]->move = KEY_RIGHT;
		else
			KEYCONF[player]->move = KEY_D;
		KEYCONF[player]->speed = 100;
		KEYCONF[player]->updated = 1;
		player++;
	}
}

static t_mlx *init_mlx(void)
{
	t_mlx *mlx;

	mlx = MEM(t_mlx);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Snake");
	mlx->image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	(mlx->data_addr = mlx_get_data_addr(mlx->image, &(mlx->bits_per_pixel),
	&(mlx->size_line), &(mlx->endian)));
	return (mlx);
}

void setup_snake(int players)
{
	t_mlx *mlx;

	srand(time(0));
	mlx = init_mlx();
	mlx->players = players;
	init_keyconf(mlx);
	init_snake(mlx);
	mlx->apple = MEM(t_apple);
	mlx_loop_hook(mlx->mlx, start_snake, mlx);
	mlx_hook(mlx->win, 4, 1L << 2, mouse_press, mlx);
	mlx_hook(mlx->win, 5, 1L << 3, mouse_release, mlx);
	mlx_hook(mlx->win, 6, 1L << 6, mouse_move, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, press_key, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, release_key, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, close_window, NULL);
	mlx_loop(mlx->mlx);
}
