/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gaze.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 00:04:40 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/29 00:18:25 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

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

static void		left_right_gaze(t_mlx *mlx)
{
	int x;
	int y;
	t_snake *tmp;
	t_colour c;

	tmp = SNAKEHEAD[0];
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
		while(tmp->next)
		{
			tmp = tmp->next;
			if (check_collision_body((t_point){x, y}, tmp))
			{
				c = (t_colour){255, 0, 0};
				break ;
			}
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x += 10;
	}
	tmp = SNAKEHEAD[0];
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
		while(tmp->next)
		{
			tmp = tmp->next;
			if (check_collision_body((t_point){x, y}, tmp))
			{
				c = (t_colour){255, 0, 0};
				break ;
			}
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x -= 10;
	}
}

void			snake_gaze(t_mlx *mlx)
{
	up_down_gaze(mlx);
	left_right_gaze(mlx);
	topleft_bottomright_gaze(mlx);
	bottomleft_topright_gaze(mlx);
}