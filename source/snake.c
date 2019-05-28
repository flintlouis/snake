/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   snake.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/08 17:09:56 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/28 23:58:30 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void    ai_snake(t_mlx *mlx); /* <----- */
void			snake_gaze(t_mlx *mlx);/* <----- */

void		add_snake_body(t_snake *snake_head)
{
	t_snake *snake_body;

	snake_body = snake_head;
	while (snake_body->next)
		snake_body = snake_body->next;
	snake_body->next = MEM(t_snake);
	snake_body->next->cur_pos = snake_body->old_pos;
	snake_body->next->old_pos = snake_body->old_pos;
}

static void	draw_snake(t_mlx *mlx, int player)
{
	t_snake *snake;
	t_colour colour[3];
	int stripes;

	stripes = 0;
	snake = SNAKEHEAD[player];
	if (player == 0)
	{
		colour[0] = (t_colour){0xFF, 0xFF, 0x00}; /* HEAD COLOUR */
		colour[1] = (t_colour){0xFF, 0xC3, 0x00};
		colour[2] = (t_colour){0xFF, 0x57, 0x33};
	}
	else
	{
		colour[0] = (t_colour){0x36, 0xFF, 0x00}; /* HEAD COLOUR */
		colour[1] = (t_colour){0x31, 0xBD, 0x0B};
		colour[2] = (t_colour){0x35, 0x90, 0x1C};
	}
	while (snake)
	{
		put_square(mlx, snake->cur_pos, colour[stripes]);
		snake = snake->next;
		stripes = (stripes + 1) % 3;
		if (stripes == 0)
			stripes++;
	}
}

static void snake(t_mlx* mlx)
{
	int player;

	player = 0;
	background(mlx);
	place_apple(mlx);
	while (player < GAME->players)
	{
		draw_snake(mlx, player);
		if (KEYCONF[player]->ms >= KEYCONF[player]->speed)
		{
			if (GAME->ai)
				ai_snake(mlx); /* AI WORK IN PROGRESS */
			move_snake(mlx, player);
			KEYCONF[player]->ms = 0;
			KEYCONF[player]->updated = 1;
		}
		player++;
	}
	if (GAME->gaze)
		snake_gaze(mlx); /* <------ */
}

static int get_player_info(t_mlx *mlx, long ms)
{
	int player;

	player = 0;
	while (player < GAME->players)
	{
		KEYCONF[player]->ms += ms;
		player++;
	}
	return (GAME->game_over);
}

int			start_snake(t_mlx *mlx)
{
	long	ms;
	
	if (GAME->menu)
		menu(mlx);
	else
	{
		ms = time_between_frames();
		if (!get_player_info(mlx, ms)) /* CHECK TO SEE IF NO PLAYER IS GAMEOVER AND GET THE SPEED */
			snake(mlx);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image, 0, 0);
	if (GAME->menu)
		menu_title(mlx);
	else
	{
		if (GAME->players == 1)
			score(mlx);
		if (GAME->start_text <= 2500)
			start_text(mlx);
		GAME->start_text += ms;
	}
	return (0);
}
