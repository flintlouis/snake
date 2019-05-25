/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ai.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 15:01:29 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/25 18:08:59 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

void	turn_left(t_mlx *mlx)
{
	
	if (KEYCONF[0]->move == KEY_RIGHT)
		KEYCONF[0]->move = KEY_UP;
	else if (KEYCONF[0]->move == KEY_UP)
		KEYCONF[0]->move = KEY_LEFT;
	else if (KEYCONF[0]->move == KEY_LEFT)
		KEYCONF[0]->move = KEY_DOWN;
	else if (KEYCONF[0]->move == KEY_DOWN)
		KEYCONF[0]->move = KEY_RIGHT;
}

void	turn_right(t_mlx *mlx)
{

	if (KEYCONF[0]->move == KEY_RIGHT)
		KEYCONF[0]->move = KEY_DOWN;
	else if (KEYCONF[0]->move == KEY_DOWN)
		KEYCONF[0]->move = KEY_LEFT;
	else if (KEYCONF[0]->move == KEY_LEFT)
		KEYCONF[0]->move = KEY_UP;
	else if (KEYCONF[0]->move == KEY_UP)
		KEYCONF[0]->move = KEY_RIGHT;
}

void	ai_box(t_mlx *mlx) /* PROTOTYPE */
{
	if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
		turn_left(mlx);
	else if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP))
		turn_right(mlx);
}

// static int check_possibility(t_mlx *mlx)
// {
// 	t_snake *tmp_head;
// 	t_snake *tmp_body;
// 	t_point tmp_prev_pos;

// 	tmp_head = SNAKEHEAD[0];
// 	tmp_body = SNAKEHEAD[0]->next;
// 	while (tmp_body)
// 	{
// 		move_snake_body(tmp_body, tmp_body->old_pos);
// 		tmp_body = tmp_body->next;
// 	}
// 	if (KEYCONF[0]->move == KEY_RIGHT)
// 		tmp_head->cur_pos.x += GRID;
// 	else if (KEYCONF[0]->move == KEY_LEFT)
// 		tmp_head->cur_pos.x -= GRID;
// 	else if (KEYCONF[0]->move == KEY_UP)
// 		tmp_head->cur_pos.y -= GRID;
// 	else if (KEYCONF[0]->move == KEY_DOWN)
// 		tmp_head->cur_pos.y += GRID;
// 	tmp_body = tmp_head->next;
// 	while (tmp_body)
// 	{
// 		if (check_collision(tmp_head, tmp_body))
// 		{
// 			turn_left(mlx);
// 			tmp_body = tmp_head;
// 		}
// 		tmp_body = tmp_body->next;
// 	}
// 	return (0);
// }

void	ai_snake(t_mlx *mlx)
{
	int side;
	int no_side;

	if ((APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
	{
		no_side = (SNAKEHEAD[0]->cur_pos.x - APPLE->pos.x) / 10;
		side = ((WIDTH - SNAKEHEAD[0]->cur_pos.x) + APPLE->pos.x) / 10;
		if (no_side <= side)
			KEYCONF[0]->move = KEY_LEFT;
		else
			KEYCONF[0]->move = KEY_RIGHT;
	}
	else if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT))
	{
		no_side = (SNAKEHEAD[0]->cur_pos.y - APPLE->pos.y) / 10;
		side = ((HEIGHT - SNAKEHEAD[0]->cur_pos.y) + APPLE->pos.y) / 10;
		if (no_side <= side)
			KEYCONF[0]->move = KEY_UP;		
		else
			KEYCONF[0]->move = KEY_DOWN;		
	}
	else if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT))
	{
		no_side = (APPLE->pos.y - SNAKEHEAD[0]->cur_pos.y) / 10;
		side = (HEIGHT - APPLE->pos.y + SNAKEHEAD[0]->cur_pos.y) / 10;
		if (no_side <= side)
			KEYCONF[0]->move = KEY_DOWN;
		else
			KEYCONF[0]->move = KEY_UP;
	}
	else if ((APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
	{
		no_side = (APPLE->pos.x - SNAKEHEAD[0]->cur_pos.x) / 10;
		side = (WIDTH - APPLE->pos.x + SNAKEHEAD[0]->cur_pos.x) / 10;
		if (no_side <= side)
			KEYCONF[0]->move = KEY_RIGHT;
		else
			KEYCONF[0]->move = KEY_LEFT;
	}
	// check_possibility(mlx);
}
