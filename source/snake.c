/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   snake.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/08 17:09:56 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/09 20:16:24 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

static void	background(t_mlx *mlx)
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
			colour = (t_colour){0x1a, 0x3a, 0x3a};
			put_square(mlx, (t_point){x, y}, colour);
			x += GRID;
		}
		y += GRID;
	}
}

void	add_snake_body(t_mlx *mlx)
{
	t_snake *snake_body;
	
	snake_body = SNAKEHEAD;
	while (snake_body->next)
		snake_body = snake_body->next;
	snake_body->next = MEM(t_snake);
	snake_body->next->cur_pos = snake_body->old_pos;
	snake_body->next->old_pos = snake_body->old_pos;
}

static int check_apple(t_mlx *mlx)
{
	int grow;

	grow = 0;
	if (SNAKEHEAD->cur_pos.x == APPLE->pos.x && SNAKEHEAD->cur_pos.y == APPLE->pos.y)
	{
		APPLE->on = 0;
		KEYCONF->score += 5;
		while (grow < 3)
		{
			add_snake_body(mlx);
			grow++;
		}
		KEYCONF->growth = (KEYCONF->growth + 1) % 4;
		if (KEYCONF->growth == 3 && KEYCONF->speed != 0)
			KEYCONF->speed -= .5;
		return (1);
	}
	return (0);
}

static int check_collision(t_snake *snake_head, t_snake *body)
{
	if (!body)
		return (0);
	if (snake_head->cur_pos.x == body->cur_pos.x && snake_head->cur_pos.y == body->cur_pos.y)
		return (1);
	return (0);
}

static void	draw_snake(t_mlx *mlx)
{
	t_snake *snake;

	snake = SNAKEHEAD;
	while (snake)
	{
		put_square(mlx, snake->cur_pos, (t_colour){0x22, 0x8B, 0x22});
		snake = snake->next;
	}
}

static void	move_snake_body(t_snake *body, t_point new_pos)
{
	body->old_pos = body->cur_pos;
	body->cur_pos = new_pos;
}

static void move_head(t_mlx *mlx, t_snake *snake)
{
		if (KEYCONF->move == KEY_RIGHT)
		{
			snake->cur_pos.x += GRID;
			snake->cur_pos.x = snake->cur_pos.x == WIDTH ? 0 : snake->cur_pos.x;			
		}
		else if (KEYCONF->move == KEY_LEFT)
		{
			snake->cur_pos.x -= GRID;
			snake->cur_pos.x= snake->cur_pos.x < 0 ? (WIDTH - GRID) : snake->cur_pos.x;
		}
		else if (KEYCONF->move == KEY_UP)
		{
			snake->cur_pos.y -= GRID;
			snake->cur_pos.y = snake->cur_pos.y < 0 ? (HEIGHT - GRID) : snake->cur_pos.y;
		}
		else if (KEYCONF->move == KEY_DOWN)
		{
			snake->cur_pos.y += GRID;
			snake->cur_pos.y = snake->cur_pos.y == HEIGHT ? 0 : snake->cur_pos.y;
		}
}

static void	move_snake(t_mlx *mlx)
{
	static double i;
	t_snake *snake;

	if (i == KEYCONF->speed)
	{	
		snake = SNAKEHEAD;
		snake->old_pos = snake->cur_pos;
		move_head(mlx, snake);
		while (snake->next)
		{
			move_snake_body(snake->next, snake->old_pos);
			snake = snake->next;
			if (check_collision(SNAKEHEAD, snake))
			{
				ft_putendl("OUCH!!!");
				KEYCONF->game_over = 1;
			}
		}
		check_apple(mlx);
		i = 0;
	}
	else
		i += .5;
}

static void place_apple(t_mlx *mlx)
{
	if (!APPLE->on)
		APPLE->pos = random_pixel();
	if (APPLE->pos.x == WIDTH)
		APPLE->pos.x -= GRID;
	if (APPLE->pos.y == HEIGHT)
		APPLE->pos.y -= GRID;
	put_square(mlx, APPLE->pos, (t_colour){0xB2, 0x22, 0x22});
	APPLE->on = 1;
}

int start_snake(t_mlx *mlx)
{
	char *score;

	if (KEYCONF->game_over == 0)
	{
		ft_bzero(mlx->data_addr, HEIGHT * WIDTH * (mlx->bits_per_pixel / 8));
		background(mlx);
		place_apple(mlx);
		draw_snake(mlx);
		move_snake(mlx);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image, 0, 0);
	score = ft_itoa(KEYCONF->score);
	mlx_string_put(mlx->mlx, mlx->win, 10, 10, 0xffffff, score);
	free(score);
	return (0);
}
