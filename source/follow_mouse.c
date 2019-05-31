/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   follow_mouse.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:36:08 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/31 12:25:33 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

static void		check_apple_side(t_mlx *mlx, int *move)
{
	int x = SNAKEHEAD[0]->cur_pos.x;
	int y = SNAKEHEAD[0]->cur_pos.y;
	int xdistance = ABS(x - GAME->mouse.x);
	int ydistance = ABS(y - GAME->mouse.y);

	if (KEYCONF[0]->move == KEY_DOWN || KEYCONF[0]->move == KEY_UP)
	{
		if (xdistance >= ydistance)
		{
			if (GAME->mouse.x > x)
				*move = KEY_RIGHT;
			else if (GAME->mouse.x < x)
				*move = KEY_LEFT;
		}
	}
	else if (KEYCONF[0]->move == KEY_LEFT || KEYCONF[0]->move == KEY_RIGHT)
	{
		if (ydistance >= xdistance)
		{
			if (GAME->mouse.y < y)
				*move = KEY_UP;
			else if (GAME->mouse.y > y)
				*move = KEY_DOWN;
		}
	}
}

static int		check_apple_back(t_mlx *mlx, int *move)
{
	int x = SNAKEHEAD[0]->cur_pos.x;
	int y = SNAKEHEAD[0]->cur_pos.y;

	if (KEYCONF[0]->move == KEY_LEFT && GAME->mouse.x > x)
	{
		if (GAME->mouse.y < y)
			turn_right(move);
		else
			turn_left(move);
		return (1);
	}
	else if (KEYCONF[0]->move == KEY_RIGHT && GAME->mouse.x < x)
	{
		if (GAME->mouse.y < y)
			turn_left(move);
		else
			turn_right(move);
		return (1);
	}
	else if (KEYCONF[0]->move == KEY_UP && GAME->mouse.y > y)
	{
		if (GAME->mouse.x < x)
			turn_left(move);
		else
			turn_right(move);
		return (1);
	}
	else if (KEYCONF[0]->move == KEY_DOWN && GAME->mouse.y < y)
	{
		if (GAME->mouse.x < x)
			turn_right(move);
		else
			turn_left(move);
		return (1);
	}
	return (0);
}

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

static int		check_body_down(t_mlx *mlx)
{
	t_snake *tmp;
	int x;
	int y;

	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	tmp = SNAKEHEAD[0];
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->cur_pos.x == x && tmp->cur_pos.y > y)
			return (ABS(y - tmp->cur_pos.y));
	}
	return (0);
}

static int		check_body_up(t_mlx *mlx)
{
	t_snake *tmp;
	int x;
	int y;

	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	tmp = SNAKEHEAD[0];
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->cur_pos.x == x && tmp->cur_pos.y < y)
			return (ABS(y - tmp->cur_pos.y));
	}
	return (0);
}

static int		check_body_right(t_mlx *mlx)
{
	t_snake *tmp;
	int x;
	int y;

	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	tmp = SNAKEHEAD[0];
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->cur_pos.y == y && tmp->cur_pos.x > x)
			return (ABS(x - tmp->cur_pos.x));
	}
	return (0);
}

static int		check_body_left(t_mlx *mlx)
{
	t_snake *tmp;
	int x;
	int y;

	x = SNAKEHEAD[0]->cur_pos.x;
	y = SNAKEHEAD[0]->cur_pos.y;
	tmp = SNAKEHEAD[0];
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->cur_pos.y == y && tmp->cur_pos.x < x)
			return (ABS(x - tmp->cur_pos.x));
	}
	return (0);
}

static int		check_box(t_mlx *mlx)
{
	if (check_body_left(mlx) && check_body_right(mlx)
	&& check_body_down(mlx) && check_body_up(mlx))
		return (1);
	return (0);
}

static int     check_apple_left(t_mlx *mlx)
{
    if ((GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
		return (1);
    return (0);
}

static int     check_apple_right(t_mlx *mlx)
{
	if ((GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN) ||
	(GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP))
		return (1);
    return (0);
}

static int     check_apple_straight(t_mlx *mlx)
{
	if ((GAME->mouse.x <= SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(GAME->mouse.x >= SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(GAME->mouse.y >= SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN) ||
	(GAME->mouse.y <= SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP))
		return (1);
    return (0);
}

static int		check_move(t_mlx *mlx, int move)
{
	t_snake *tmp;
	int x = SNAKEHEAD[0]->cur_pos.x;
	int y = SNAKEHEAD[0]->cur_pos.y;

	if (move == KEY_UP)
		y -= GRID;
	else if (move == KEY_DOWN)
		y += GRID;
	else if (move == KEY_LEFT)
		x -= GRID;
	else if (move == KEY_RIGHT)
		x += GRID;
	if (x < GRID || y < GRID || x >= WIDTH - GRID || y >= HEIGHT - GRID)
		return (1);
	tmp = SNAKEHEAD[0];
	while (tmp->next->next)
	{
		tmp = tmp->next; /* STOPS ONE BEFORE THE TAIL */
		if (x == tmp->cur_pos.x && y == tmp->cur_pos.y)
			return (1);
	}
	return (0);
}

static int		check_straight(t_mlx *mlx)
{
	int distance;

	if (KEYCONF[0]->move == KEY_UP)
	{
		if (!(distance = check_body_up(mlx)))
			distance = SNAKEHEAD[0]->cur_pos.y;
		return (distance);
	}
	else if (KEYCONF[0]->move == KEY_DOWN)
	{
		if (!(distance = check_body_down(mlx)))
			distance = HEIGHT - SNAKEHEAD[0]->cur_pos.y - GRID;
		return (distance);
	}
	else if (KEYCONF[0]->move == KEY_LEFT)
	{
		if (!(distance = check_body_left(mlx)))
			distance = SNAKEHEAD[0]->cur_pos.x;
		return (distance);
	}
	else
	{
		if (!(distance = check_body_right(mlx)))
			distance = WIDTH - SNAKEHEAD[0]->cur_pos.x - GRID;
		return (distance);
	}
}

static void		make_new_move(t_mlx *mlx, int *move)
{
	int distance1;
	int distance2;
	int straight;

	straight = check_straight(mlx);
	if (KEYCONF[0]->move == KEY_UP || KEYCONF[0]->move == KEY_DOWN)
	{
		if (!(distance1 = check_body_left(mlx)))
			distance1 = SNAKEHEAD[0]->cur_pos.x;
		if (!(distance2 = check_body_right(mlx)))
			distance2 = WIDTH - SNAKEHEAD[0]->cur_pos.x - GRID;
		if (straight >= distance1 && straight >= distance2)
			*move = KEYCONF[0]->move;
		else if (distance1 >= distance2)
			*move = KEY_LEFT;
		else
			*move = KEY_RIGHT;	
	}
	else if (KEYCONF[0]->move == KEY_LEFT || KEYCONF[0]->move == KEY_RIGHT)
	{
		if (!(distance1 = check_body_up(mlx)))
			distance1 = SNAKEHEAD[0]->cur_pos.y;
		if (!(distance2 = check_body_down(mlx)))
			distance2 = HEIGHT - SNAKEHEAD[0]->cur_pos.y - GRID;
		if (straight >= distance1 && straight >= distance2)
			*move = KEYCONF[0]->move;
		else if (distance1 >= distance2)
			*move = KEY_UP;
		else
			*move = KEY_DOWN;
	}
}

void    		follow_mouse(t_mlx *mlx)
{
	int move;

	move = KEYCONF[0]->move;
    if (check_apple_left(mlx))
        turn_left(&move);
    else if (check_apple_right(mlx))
        turn_right(&move);
    else if (check_apple_back(mlx, &move));
	else
		check_apple_side(mlx, &move);
	if (check_move(mlx, move))
		make_new_move(mlx, &move);
	KEYCONF[0]->move = move;
}
