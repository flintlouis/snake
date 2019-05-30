/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   follow_mouse.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:36:08 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/30 17:00:35 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

void no_sides(t_snake *snake);

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

static int ai_map1(t_mlx *mlx, int *move)
{
	int side;
	int no_side;

	if ((GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
	{
		no_side = (SNAKEHEAD[0]->cur_pos.x - GAME->mouse.x);
		side = ((WIDTH - SNAKEHEAD[0]->cur_pos.x) + GAME->mouse.x);
		if (no_side <= side)
			*move = KEY_LEFT;
		else
			*move = KEY_RIGHT;
	}
	else if ((GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT))
	{
		no_side = (SNAKEHEAD[0]->cur_pos.y - GAME->mouse.y);
		side = ((HEIGHT - SNAKEHEAD[0]->cur_pos.y) + GAME->mouse.y);
		if (no_side <= side)
			*move = KEY_UP;		
		else
			*move = KEY_DOWN;		
	}
	else if ((GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT))
	{
		no_side = (GAME->mouse.y - SNAKEHEAD[0]->cur_pos.y);
		side = (HEIGHT - GAME->mouse.y + SNAKEHEAD[0]->cur_pos.y);
		if (no_side <= side)
			*move = KEY_DOWN;
		else
			*move = KEY_UP;
	}
	else if ((GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
	{
		no_side = (GAME->mouse.x - SNAKEHEAD[0]->cur_pos.x);
		side = (WIDTH - GAME->mouse.x + SNAKEHEAD[0]->cur_pos.x);
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
	if ((GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP) ||
	(GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN))
		turn_left(move);
	else if ((GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y < SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_LEFT) ||
	(GAME->mouse.x == SNAKEHEAD[0]->cur_pos.x && GAME->mouse.y > SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_RIGHT) ||
	(GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x < SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_DOWN) ||
	(GAME->mouse.y == SNAKEHEAD[0]->cur_pos.y && GAME->mouse.x > SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_UP))
		turn_right(move);
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
		if ((crashed = check_collision_body(copied_snake[0]->cur_pos, tmp_cp)))
			break ;
	}
	delete_snake(copied_snake[0]);
	free(copied_snake);
	return (crashed);
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

static int		calc_apple_behind_width(t_mlx *mlx)
{
	int half_width;

	half_width = WIDTH / 2;
	if (SNAKEHEAD[0]->cur_pos.y != GAME->mouse.y && KEYCONF[0]->move == KEY_RIGHT &&
	GAME->mouse.x >= half_width && SNAKEHEAD[0]->cur_pos.x < half_width)
		return (1);
	else if (SNAKEHEAD[0]->cur_pos.y != GAME->mouse.y && KEYCONF[0]->move == KEY_LEFT &&
	GAME->mouse.x <= half_width && SNAKEHEAD[0]->cur_pos.x > half_width)
		return (1);
	return (0);
}

static int		calc_apple_behind_height(t_mlx *mlx)
{
	int half_height;

	half_height = HEIGHT / 2;
	if (SNAKEHEAD[0]->cur_pos.x != GAME->mouse.x && KEYCONF[0]->move == KEY_UP &&
	GAME->mouse.y <= half_height && SNAKEHEAD[0]->cur_pos.y > half_height)
		return (1);
	else if (SNAKEHEAD[0]->cur_pos.x != GAME->mouse.x && KEYCONF[0]->move == KEY_DOWN &&
	GAME->mouse.y >= half_height && SNAKEHEAD[0]->cur_pos.y < half_height)
		return (1);
	return (0);
}

void	calc_apple_turn(t_mlx *mlx, int *move)
{
	if (calc_apple_behind_height(mlx) || (GAME->mouse.x != SNAKEHEAD[0]->cur_pos.x && /* APPLE BEHIND SNAKEHEAD */
	((GAME->mouse.y >= SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_UP) ||
	(GAME->mouse.y <= SNAKEHEAD[0]->cur_pos.y && KEYCONF[0]->move == KEY_DOWN))))
	{
		if (GAME->mouse.x >= 0 && GAME->mouse.x < SNAKEHEAD[0]->cur_pos.x)
			*move = KEY_LEFT;
		else
			*move = KEY_RIGHT;
	}
	else if (calc_apple_behind_width(mlx) || (GAME->mouse.y != SNAKEHEAD[0]->cur_pos.y && /* APPLE BEHIND SNAKEHEAD */
	((GAME->mouse.x >= SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_LEFT) ||
	(GAME->mouse.x <= SNAKEHEAD[0]->cur_pos.x && KEYCONF[0]->move == KEY_RIGHT))))
	{
		if (GAME->mouse.y >= 0 && GAME->mouse.y < SNAKEHEAD[0]->cur_pos.y)
			*move = KEY_UP;
		else
			*move = KEY_DOWN;
	}
}

void	follow_mouse(t_mlx *mlx) /* PREV. AI */
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
