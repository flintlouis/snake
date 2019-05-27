/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ai.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 15:01:29 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/27 15:01:05 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

static int		calc_apple_behind_width(t_mlx *mlx)
{
	int half_width;

	half_width = WIDTH / 2;
	if (SNAKEHEAD[0]->cur_pos.y != APPLE->pos.y && KEYCONF[0]->move == KEY_RIGHT &&
	APPLE->pos.x >= half_width && SNAKEHEAD[0]->cur_pos.x < half_width)
		return (1);
	else if (SNAKEHEAD[0]->cur_pos.y != APPLE->pos.y && KEYCONF[0]->move == KEY_LEFT &&
	APPLE->pos.x <= half_width && SNAKEHEAD[0]->cur_pos.x > half_width)
		return (1);
	return (0);
}

static int		calc_apple_behind_height(t_mlx *mlx)
{
	int half_height;

	half_height = HEIGHT / 2;
	if (SNAKEHEAD[0]->cur_pos.x != APPLE->pos.x && KEYCONF[0]->move == KEY_UP &&
	APPLE->pos.y <= half_height && SNAKEHEAD[0]->cur_pos.y > half_height)
		return (1);
	else if (SNAKEHEAD[0]->cur_pos.x != APPLE->pos.x && KEYCONF[0]->move == KEY_DOWN &&
	APPLE->pos.y >= half_height && SNAKEHEAD[0]->cur_pos.y < half_height)
		return (1);
	return (0);
}

void	calc_apple_turn(t_mlx *mlx, int *move)
{
	if (calc_apple_behind_height(mlx) || (APPLE->pos.x != SNAKEHEAD[0]->cur_pos.x && /* APPLE BEHIND SNAKEHEAD */
	((APPLE->pos.y >= SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_UP) ||
	(APPLE->pos.y <= SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_DOWN))))
	{
		if (APPLE->pos.x >= 0 && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x)
			*move = KEY_LEFT;
		else
			*move = KEY_RIGHT;
	}
	else if (calc_apple_behind_width(mlx) || (APPLE->pos.y != SNAKEHEAD[0]->cur_pos.y && /* APPLE BEHIND SNAKEHEAD */
	((APPLE->pos.x >= SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_LEFT) ||
	(APPLE->pos.x <= SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_RIGHT))))
	{
		if (APPLE->pos.y >= 0 && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y)
			*move = KEY_UP;
		else
			*move = KEY_DOWN;
	}
}

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

static int check_possibility(t_mlx *mlx, int move) /* WORK IN PROGRESS */
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

static int ai_map1(t_mlx *mlx, int *move)
{
	int side;
	int no_side;

	if ((APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
	{
		no_side = (SNAKEHEAD[0]->cur_pos.x - APPLE->pos.x);
		side = ((WIDTH - SNAKEHEAD[0]->cur_pos.x) + APPLE->pos.x);
		if (no_side <= side)
			*move = KEY_LEFT;
		else
			*move = KEY_RIGHT;
	}
	else if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT))
	{
		no_side = (SNAKEHEAD[0]->cur_pos.y - APPLE->pos.y);
		side = ((HEIGHT - SNAKEHEAD[0]->cur_pos.y) + APPLE->pos.y);
		if (no_side <= side)
			*move = KEY_UP;		
		else
			*move = KEY_DOWN;		
	}
	else if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT))
	{
		no_side = (APPLE->pos.y - SNAKEHEAD[0]->cur_pos.y);
		side = (HEIGHT - APPLE->pos.y + SNAKEHEAD[0]->cur_pos.y);
		if (no_side <= side)
			*move = KEY_DOWN;
		else
			*move = KEY_UP;
	}
	else if ((APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
	{
		no_side = (APPLE->pos.x - SNAKEHEAD[0]->cur_pos.x);
		side = (WIDTH - APPLE->pos.x + SNAKEHEAD[0]->cur_pos.x);
		if (no_side <= side)
			*move = KEY_RIGHT;
		else
			*move = KEY_LEFT;
	}
	else
		return (0);
	return (1);
}

static void	ai_map2(t_mlx *mlx, int *move)
{
	if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
		turn_left(move);
	else if ((APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(APPLE->pos.x == SNAKEHEAD[0]->cur_pos.x && APPLE->pos.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN) ||
	(APPLE->pos.y == SNAKEHEAD[0]->cur_pos.y && APPLE->pos.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP))
		turn_right(move);
}

void	check_ai(t_mlx *mlx, int *move)
{
	int time_out;

	time_out = 0;
	while (check_possibility(mlx, *move) && time_out < 4)
	{
		if (!time_out)
			calc_apple_turn(mlx, move);
		else
			turn_left(move);
		time_out++;
	}

}

/* 
** FUNCTION CHECK RIGHT/LEFT/STRAIGHT = FREE? HOW FAR IS FREE (IF HITS BODY CALC HOW FAR AWAY THE TAIL IS VS DISTANCE BEFORE HITTING)
** FUNCTION WHERE IS APPLE
*/

void	ai_snake(t_mlx *mlx) /* LOOKS COOL AND FASTER BUT LESS EFFECTIVE */
{
	int move;

	move = KEYCONF[0]->move;
	if (GAME->map == KEY_1)
	{
		if (!ai_map1(mlx, &move))
			calc_apple_turn(mlx, &move);
	}
	else if (GAME->map == KEY_2)
		ai_map2(mlx, &move);
	check_ai(mlx, &move);	
	KEYCONF[0]->move = move;
}

void	ai_snake1(t_mlx *mlx) /* SIMPLE BUT MOST EFFECTIVE */
{
	int move;

	move = KEYCONF[0]->move;
	if (GAME->map == KEY_1)
		ai_map1(mlx, &move);
	else if (GAME->map == KEY_2)
		ai_map2(mlx, &move);
	check_ai(mlx, &move);
	KEYCONF[0]->move = move;
}
