/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ai.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 15:01:29 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/28 23:56:18 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

/* 
** FUNCTION CHECK RIGHT/LEFT/STRAIGHT = FREE? HOW FAR IS FREE (IF HITS BODY CALC HOW FAR AWAY THE TAIL IS VS DISTANCE BEFORE HITTING)
** FUNCTION WHERE IS APPLE
*/

void			put_pixel(int x, int y, t_mlx *mlx, t_colour colour); /* <----- */

static void		bottomleft_topright_gaze(t_mlx *mlx)
{
	int x;
	int y;
	t_colour c;

	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	while (x > 0 && y > 0)
	{
		if (APPLE->pos.x == x && APPLE->pos.y == y)
		{
			system("clear");
			printf("Distance to apple %d moves\n",
			(((ABS(APPLE->pos.x - SNAKEHEAD[0]->cur_pos.x)) + ABS(APPLE->pos.y - SNAKEHEAD[0]->cur_pos.y))) / 10);
			c = (t_colour){0, 0, 0};
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x -= 10;
		y += 10;
	}
	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	while (x < WIDTH && y < HEIGHT)
	{
		if (APPLE->pos.x == x && APPLE->pos.y == y)
		{
			system("clear");
			printf("Distance to apple %d moves\n",
			(((ABS(APPLE->pos.x - SNAKEHEAD[0]->cur_pos.x)) + ABS(APPLE->pos.y - SNAKEHEAD[0]->cur_pos.y))) / 10);
			c = (t_colour){0, 0, 0};
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x += 10;
		y -= 10;
	}
}

static void		topleft_bottomright_gaze(t_mlx *mlx)
{
	int x;
	int y;
	t_colour c;

	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	while (x > 0 && y > 0)
	{
		if (APPLE->pos.x == x && APPLE->pos.y == y)
		{
			system("clear");
			printf("Distance to apple %d moves\n",
			(((ABS(APPLE->pos.x - SNAKEHEAD[0]->cur_pos.x)) + ABS(APPLE->pos.y - SNAKEHEAD[0]->cur_pos.y))) / 10);
			c = (t_colour){0, 0, 0};
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x -= 10;
		y -= 10;
	}
	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	while (x < WIDTH && y < HEIGHT)
	{
		if (APPLE->pos.x == x && APPLE->pos.y == y)
		{
			system("clear");
			printf("Distance to apple %d moves\n",
			(((ABS(APPLE->pos.x - SNAKEHEAD[0]->cur_pos.x)) + ABS(APPLE->pos.y - SNAKEHEAD[0]->cur_pos.y))) / 10);
			c = (t_colour){0, 0, 0};
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x += 10;
		y += 10;
	}
}

static void		left_right_gaze(t_mlx *mlx)
{
	int x;
	int y;
	t_colour c;

	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	while (x < WIDTH)
	{
		if (APPLE->pos.x == x && APPLE->pos.y == y)
		{
			system("clear");
			printf("Distance to apple %d moves\n", (APPLE->pos.x - SNAKEHEAD[0]->cur_pos.x) / 10);
			c = (t_colour){0, 0, 0};
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x += 10;
	}
	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	while (x > 0)
	{
		if (APPLE->pos.x == x && APPLE->pos.y == y)
		{
			system("clear");
			printf("Distance to apple %d moves\n", (ABS(APPLE->pos.x - SNAKEHEAD[0]->cur_pos.x)) / 10);
			c = (t_colour){0, 0, 0};
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x -= 10;
	}
}

static void		up_down_gaze(t_mlx *mlx)
{
	int x;
	int y;
	t_colour c;

	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	while (y < HEIGHT)
	{
		if (APPLE->pos.x == x && APPLE->pos.y == y)
		{
			system("clear");
			printf("Distance to apple %d moves\n", (APPLE->pos.y - SNAKEHEAD[0]->cur_pos.y) / 10);
			c = (t_colour){0, 0, 0};
		}
		put_pixel(x + 5, y + 5, mlx, c);
		y += 10;
	}
	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	while (y > 0)
	{
		if (APPLE->pos.x == x && APPLE->pos.y == y)
		{
			system("clear");
			printf("Distance to apple %d moves\n", (ABS(APPLE->pos.y - SNAKEHEAD[0]->cur_pos.y)) / 10);
			c = (t_colour){0, 0, 0};
		}
		put_pixel(x + 5, y + 5, mlx, c);
		y -= 10;
	}
}

void			snake_gaze(t_mlx *mlx)
{
	up_down_gaze(mlx);
	left_right_gaze(mlx);
	topleft_bottomright_gaze(mlx);
	bottomleft_topright_gaze(mlx);
}

static int     check_apple_left(t_mlx *mlx)
{
    if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
		return (1);
    return (0);
}

static int     check_apple_right(t_mlx *mlx)
{
	if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP))
		return (1);
    return (0);
}

static int     check_apple_straight(t_mlx *mlx)
{
	if ((APPLE->pos.x <= SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(APPLE->pos.x >= SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.y >= SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN) ||
	(APPLE->pos.y <= SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP))
		return (1);
    return (0);
}

void    ai_snake(t_mlx *mlx)
{
    if (check_apple_left(mlx))
        ft_putendl("left");
        turn_left(&(KEYCONF[0]->move));
    // else if (check_apple_right(mlx))
        ft_putendl("right");
        turn_right(&(KEYCONF[0]->move));
    // else if (check_apple_straight(mlx))
        // KEYCONF[0]->speed = 30;
        ft_putendl("straight");
    // else if (!check_apple_straight(mlx))
        // KEYCONF[0]->speed = 100;
}