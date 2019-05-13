/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   snake.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/08 17:09:56 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/13 19:07:36 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void	add_snake_body(t_mlx *mlx, int player)
{
	t_snake *snake_body;

	snake_body = SNAKEHEAD[player];
	while (snake_body->next)
		snake_body = snake_body->next;
	snake_body->next = MEM(t_snake);
	snake_body->next->cur_pos = snake_body->old_pos;
	snake_body->next->old_pos = snake_body->old_pos;
}

void	draw_snake(t_mlx *mlx, int player)
{
	t_snake *snake;
	t_colour colour1[2];
	t_colour colour2[2];
	int stripes;

	stripes = 0;
	snake = SNAKEHEAD[player];
	if (player == 0)
	{	
		colour1[0] = (t_colour){0xED, 0x52, 0x24};
		colour1[1] = (t_colour){0xED, 0xEA, 0x24};
	}
	else
	{
		colour1[0] = (t_colour){0x22, 0x8B, 0x22};
		colour1[1] = (t_colour){0x00, 0x00, 0x00};
	}
	while (snake)
	{
		put_square(mlx, snake->cur_pos, colour1[stripes]);
		snake = snake->next;
		stripes = (stripes + 1) % 2;
	}
}

static int get_player_info(t_mlx *mlx, long ms)
{
	int player;

	player = 0;
	while (player < mlx->players)
	{
		KEYCONF[player]->ms += ms;
		if (KEYCONF[player]->game_over == 1)
			return (1);
		player++;
	}
	return (0);
}

static void snake(t_mlx* mlx)
{
	int player;

	player = 0;
	if (KEYCONF[0]->ms >= KEYCONF[0]->speed) /* HOW TO DO THIS WITH 2 PLAYERS */
	{
		background(mlx);
		place_apple(mlx);
		// ft_bzero(mlx->data_addr, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
		while (player < mlx->players)
		{
			draw_snake(mlx, player);
			move_snake(mlx, player);
			KEYCONF[player]->ms = 0;
			player++;
		}
	}
}

int start_snake(t_mlx *mlx)
{
	char		*score;
	long		ms;

	ms = time_between_frames();
	if (!get_player_info(mlx, ms)) /* IF NO PLAYER IS GAMEOVER */
		snake(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image, 0, 0);
	score = ft_itoa(KEYCONF[0]->score);
	mlx_string_put(mlx->mlx, mlx->win, (WIDTH - 30), 20, 0xffffff, score);
	free(score);
	if (mlx->players == 2)
	{
		score = ft_itoa(KEYCONF[1]->score);
		mlx_string_put(mlx->mlx, mlx->win, 20, 20, 0xffffff, score);
		free(score);
	}
	return (0);
}
