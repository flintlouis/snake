/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vision.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 00:04:40 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/30 00:13:52 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

static int		count_tail(t_snake *snake)
{
	int tail;
	t_snake *tmp;

	tail = 0;
	tmp = snake;
	while (tmp->next)
	{
		tmp = tmp->next;
		tail++;
	}
	return (tail);
}

static void		bottomleft_topright_vision(t_mlx *mlx)
{
	int x;
	int y;
	t_colour c;
	t_snake *tmp;

	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	while (x >= 0 && y >= 0)
	{
		tmp = SNAKEHEAD[0];
		if (APPLE->pos.x == x && APPLE->pos.y == y)
			c = (t_colour){0, 0, 0};
		while(tmp->next)
		{
			tmp = tmp->next;
			if (tmp->cur_pos.x == x && tmp->cur_pos.y == y)
			{
				c = (t_colour){255, 0, 0};
				break ;
			}
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
		tmp = SNAKEHEAD[0];
		if (APPLE->pos.x == x && APPLE->pos.y == y)
			c = (t_colour){0, 0, 0};
		while(tmp->next)
		{
			tmp = tmp->next;
			if (tmp->cur_pos.x == x && tmp->cur_pos.y == y)
			{
				c = (t_colour){255, 0, 0};
				break ;
			}
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x += 10;
		y -= 10;
	}
}

static void		topleft_bottomright_vision(t_mlx *mlx)
{
	int x;
	int y;
	t_colour c;
	t_snake *tmp;

	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	while (x >= 0 && y >= 0)
	{
		tmp = SNAKEHEAD[0];
		if (APPLE->pos.x == x && APPLE->pos.y == y)
			c = (t_colour){0, 0, 0};
		while(tmp->next)
		{
			tmp = tmp->next;
			if (tmp->cur_pos.x == x && tmp->cur_pos.y == y)
			{
				c = (t_colour){255, 0, 0};
				break ;
			}
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
		tmp = SNAKEHEAD[0];
		if (APPLE->pos.x == x && APPLE->pos.y == y)
			c = (t_colour){0, 0, 0};
		while(tmp->next)
		{
			tmp = tmp->next;
			if (tmp->cur_pos.x == x && tmp->cur_pos.y == y)
			{
				c = (t_colour){255, 0, 0};
				break ;
			}
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x += 10;
		y += 10;
	}
}

int		down_vision(t_mlx *mlx)
{
	int x;
	int y;
	t_colour c;
	t_snake *tmp;
	int distance;

	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	distance = HEIGHT - SNAKEHEAD[0]->cur_pos.y;
	/* DOWN */
	while (y < HEIGHT)
	{
		tmp = SNAKEHEAD[0];
		if (APPLE->pos.x == x && APPLE->pos.y == y)
			c = (t_colour){0, 0, 0};
		while(tmp->next)
		{
			tmp = tmp->next;
			if (tmp->cur_pos.x == x && tmp->cur_pos.y == y)
			{
				c = (t_colour){255, 0, 0};
				distance = ABS(SNAKEHEAD[0]->cur_pos.y - tmp->cur_pos.y);
				break ;
			}
		}
		put_pixel(x + 5, y + 5, mlx, c);
		y += 10;
	}
	return (distance);
}

int		up_vision(t_mlx *mlx)
{
	int x;
	int y;
	t_colour c;
	t_snake *tmp;
	int distance;

	c = (t_colour){255, 255, 255};
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	distance = y;
	/* UP */
	while (y >= 0)
	{
		tmp = SNAKEHEAD[0];
		if (APPLE->pos.x == x && APPLE->pos.y == y)
			c = (t_colour){0, 0, 0};
		while(tmp->next)
		{
			tmp = tmp->next;
			if (tmp->cur_pos.x == x && tmp->cur_pos.y == y)
			{
				c = (t_colour){255, 0, 0};
				distance = ABS(SNAKEHEAD[0]->cur_pos.y - tmp->cur_pos.y);
				break ;
			}
		}
		put_pixel(x + 5, y + 5, mlx, c);
		y -= 10;
	}
	return (distance);
}

int		left_vision(t_mlx *mlx)
{
	int x;
	int y;
	t_snake *tmp;
	t_colour c;
	int distance;
	
	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	c = (t_colour){255, 255, 255};
	distance = x;
	/* LEFT */
	while (x >= 0)
	{
		tmp = SNAKEHEAD[0];
		if (APPLE->pos.x == x && APPLE->pos.y == y)
			c = (t_colour){0, 0, 0};
		while(tmp->next)
		{
			tmp = tmp->next;
			if (tmp->cur_pos.y == y && tmp->cur_pos.x == x)
			{
				c = (t_colour){255, 0, 0};
				distance = ABS(SNAKEHEAD[0]->cur_pos.x - tmp->cur_pos.x);
				break ;
			}
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x -= 10;
	}
	return (distance);
}

int		right_vision(t_mlx *mlx)
{
	int x;
	int y;
	t_snake *tmp;
	t_colour c;
	int distance;

	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	c = (t_colour){255, 255, 255};
	distance = WIDTH - SNAKEHEAD[0]->cur_pos.x;
	/* RIGHT */
	while (x < WIDTH)
	{
		tmp = SNAKEHEAD[0];
		if (APPLE->pos.x == x && APPLE->pos.y == y)
			c = (t_colour){0, 0, 0};
		while(tmp->next)
		{
			tmp = tmp->next;
			if (tmp->cur_pos.y == y && tmp->cur_pos.x == x)
			{
				c = (t_colour){255, 0, 0};
				distance = ABS(SNAKEHEAD[0]->cur_pos.x - tmp->cur_pos.x);
				break ;
			}
		}
		put_pixel(x + 5, y + 5, mlx, c);
		x += 10;
	}
	return (distance);
}

void			snake_vision(t_mlx *mlx)
{
	down_vision(mlx);
	up_vision(mlx);
	left_vision(mlx);
	right_vision(mlx);
	topleft_bottomright_vision(mlx);
	bottomleft_topright_vision(mlx);
}