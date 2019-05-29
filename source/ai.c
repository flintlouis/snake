/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ai.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 15:01:29 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/29 11:09:49 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

/* 
** FUNCTION CHECK RIGHT/LEFT/STRAIGHT = FREE? HOW FAR IS FREE (IF HITS BODY CALC HOW FAR AWAY THE TAIL IS VS DISTANCE BEFORE HITTING)
** FUNCTION WHERE IS APPLE
*/

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
        // turn_left(&(KEYCONF[0]->move));
    else if (check_apple_right(mlx))
        ft_putendl("right");
        // turn_right(&(KEYCONF[0]->move));
    else if (check_apple_straight(mlx))
        ft_putendl("straight");
        // KEYCONF[0]->speed = 30;
    // else if (!check_apple_straight(mlx))
        // KEYCONF[0]->speed = 100;
}