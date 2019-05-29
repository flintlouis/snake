/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ai.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 15:01:29 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/30 00:13:58 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

/* 
** FUNCTION CHECK RIGHT/LEFT/STRAIGHT = FREE? HOW FAR IS FREE (IF HITS BODY CALC HOW FAR AWAY THE TAIL IS VS DISTANCE BEFORE HITTING)
** FUNCTION WHERE IS APPLE
*/

int		down_vision(t_mlx *mlx);
int		up_vision(t_mlx *mlx);
int		left_vision(t_mlx *mlx);
int		right_vision(t_mlx *mlx);

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

static void	make_new_move(t_mlx *mlx, int *move)
{
	int i;
	int j;

	if (KEYCONF[0]->move == KEY_UP || KEYCONF[0]->move == KEY_DOWN)
	{
		i = left_vision(mlx);
		j = right_vision(mlx);
		if (i >= j)
			*move = KEY_LEFT;
		else
			*move = KEY_RIGHT;
	}
	else if (KEYCONF[0]->move == KEY_LEFT || KEYCONF[0]->move == KEY_RIGHT)
	{
		i = up_vision(mlx);
		j = down_vision(mlx);
		if (i >= j)
			*move = KEY_UP;
		else
			*move = KEY_DOWN;

	}
}

void    ai_snake(t_mlx *mlx)
{
	int move;
	
	move = KEYCONF[0]->move;
    if (check_apple_left(mlx))
        // ft_putendl("left");
        turn_left(&move);
    else if (check_apple_right(mlx))
        // ft_putendl("right");
        turn_right(&move);
    // else if (check_apple_straight(mlx))
    //     // ft_putendl("straight");
    //     KEYCONF[0]->speed = 30;
    // else if (!check_apple_straight(mlx))
    //     KEYCONF[0]->speed = 100;
	if (check_move(mlx, move))
		make_new_move(mlx, &move);
	KEYCONF[0]->move = move;
}