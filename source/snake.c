/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   snake.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/08 17:09:56 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/10 14:37:09 by fhignett      ########   odam.nl         */
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

	snake = SNAKEHEAD[player];
	while (snake)
	{
		put_square(mlx, snake->cur_pos, (t_colour){0x22, 0x8B, 0x22});
		snake = snake->next;
	}
}

static void	ft_wait(t_mlx *mlx)
{
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = KEYCONF->speed;
	nanosleep(&tim, &tim2);
}

int start_snake(t_mlx *mlx)
{
	char *score;
	int player;
	

	player = 0;
	if (KEYCONF->game_over == 0)
	{
		ft_bzero(mlx->data_addr, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
		background(mlx);
		place_apple(mlx);
		while (player < mlx->players)
		{
			move_snake(mlx, player);
			draw_snake(mlx, player);
			player++;
		}
		ft_wait(mlx);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image, 0, 0);
	score = ft_itoa(KEYCONF->score);
	mlx_string_put(mlx->mlx, mlx->win, 10, 10, 0xffffff, score);
	free(score);
	return (0);
}
