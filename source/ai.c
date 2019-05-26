/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ai.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 15:01:29 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/26 17:48:38 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

void	turn_left(int *move)
{
	if (*move == KEY_RIGHT)
		*move = KEY_UP;
	else if (*move == KEY_UP)
		*move = KEY_LEFT;
	else if (*move == KEY_LEFT)
		*move = KEY_DOWN;
	else if (*move == KEY_DOWN)
		*move = KEY_RIGHT;
}

void	turn_right(int *move)
{
	if (*move == KEY_RIGHT)
		*move = KEY_DOWN;
	else if (*move == KEY_DOWN)
		*move = KEY_LEFT;
	else if (*move == KEY_LEFT)
		*move = KEY_UP;
	else if (*move == KEY_UP)
		*move = KEY_RIGHT;
}

static t_snake **copy_snake(t_mlx *mlx)
{
	t_snake **copy_snake;
	t_snake *tmp_cp;
	t_snake *tmp_og;

	copy_snake = (t_snake**)malloc(sizeof(t_snake*));
	copy_snake[0] = MEM(t_snake);
	copy_snake[0]->cur_pos = SNAKEHEAD[0]->cur_pos;
	copy_snake[0]->old_pos = SNAKEHEAD[0]->old_pos;
	tmp_cp = copy_snake[0];
	tmp_og = SNAKEHEAD[0];
	while (tmp_og->next)
	{
		add_snake_body(copy_snake[0]);
		tmp_cp = tmp_cp->next;
		tmp_og = tmp_og->next;
		tmp_cp->cur_pos = tmp_og->cur_pos;
		tmp_cp->old_pos = tmp_og->old_pos;
	}
	return(copy_snake);
}

static int check_possibility(t_mlx *mlx, int move)
{
	t_snake **copied_snake;
	t_snake *tmp_cp;
	int crashed;

	crashed = 0;
	copied_snake = copy_snake(mlx);
	tmp_cp = copied_snake[0];
	move_snake_head(tmp_cp, move);
	if (GAME->map == KEY_1)
		no_sides(tmp_cp);
	// if (GAME->players == 2 && check_collision_player(mlx, player)) /* HEAD-ON COLLISION LOOKS WIERD */
	// 	game_over(mlx, player);
	else if (GAME->map == KEY_2 && check_sides_collision(tmp_cp))
	{
		delete_snake(copied_snake[0]);
		free(copied_snake);
		return (1);
	}
	// else if (GAME->map == KEY_3)
	// {
	// 	map3_sides(snake);
	// 	if (check_map3_collision(SNAKEHEAD[player]))
	// 		game_over(mlx, player);
	// }

	while (tmp_cp->next)
	{
		move_snake_body(tmp_cp->next, tmp_cp->old_pos);
		tmp_cp = tmp_cp->next;
		if ((crashed = check_collision(copied_snake[0], tmp_cp)))
			break ;
	}
	delete_snake(copied_snake[0]);
	free(copied_snake);
	return (crashed);
}

void	ai_snake(t_mlx *mlx)
{
	int move;
	int side;
	int no_side;
	int time_out;

	move = KEYCONF[0]->move;
	if ((APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
	{
		no_side = (SNAKEHEAD[0]->cur_pos.x - APPLE->pos.x) / 10;
		side = ((WIDTH - SNAKEHEAD[0]->cur_pos.x) + APPLE->pos.x) / 10;
		if (no_side <= side)
			move = KEY_LEFT;
		else
			move = KEY_RIGHT;
	}
	else if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT))
	{
		no_side = (SNAKEHEAD[0]->cur_pos.y - APPLE->pos.y) / 10;
		side = ((HEIGHT - SNAKEHEAD[0]->cur_pos.y) + APPLE->pos.y) / 10;
		if (no_side <= side)
			move = KEY_UP;		
		else
			move = KEY_DOWN;		
	}
	else if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT))
	{
		no_side = (APPLE->pos.y - SNAKEHEAD[0]->cur_pos.y) / 10;
		side = (HEIGHT - APPLE->pos.y + SNAKEHEAD[0]->cur_pos.y) / 10;
		if (no_side <= side)
			move = KEY_DOWN;
		else
			move = KEY_UP;
	}
	else if ((APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
	{
		no_side = (APPLE->pos.x - SNAKEHEAD[0]->cur_pos.x) / 10;
		side = (WIDTH - APPLE->pos.x + SNAKEHEAD[0]->cur_pos.x) / 10;
		if (no_side <= side)
			move = KEY_RIGHT;
		else
			move = KEY_LEFT;
	}
	time_out = 0;
	while (check_possibility(mlx, move) && time_out++ < 3)
		turn_left(&move);
	KEYCONF[0]->move = move;
}
