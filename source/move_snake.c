/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_snake.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/09 22:17:52 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/30 16:59:31 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

void		turn_left(int *move)
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

void		turn_right(int *move)
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

static void map3_sides(t_snake *snake)
{
	snake->cur_pos.x = snake->cur_pos.x < 0 && (snake->cur_pos.y >= 150 && snake->cur_pos.y <= 230) ? (WIDTH - GRID) : snake->cur_pos.x;
	snake->cur_pos.x = snake->cur_pos.x >= WIDTH && (snake->cur_pos.y >= 150 && snake->cur_pos.y <= 230) ? 0 : snake->cur_pos.x;
	snake->cur_pos.y = snake->cur_pos.y < 0 && (snake->cur_pos.x >= 250 && snake->cur_pos.x <= 330) ? (HEIGHT - GRID) : snake->cur_pos.y;
	snake->cur_pos.y = snake->cur_pos.y >= HEIGHT && (snake->cur_pos.x >= 250 && snake->cur_pos.x <= 330) ? 0 : snake->cur_pos.y;
}

void 		no_sides(t_snake *snake)
{
	snake->cur_pos.x = snake->cur_pos.x >= WIDTH ? 0 : snake->cur_pos.x;
	snake->cur_pos.x = snake->cur_pos.x < 0 ? (WIDTH - GRID) : snake->cur_pos.x;
	snake->cur_pos.y = snake->cur_pos.y < 0 ? (HEIGHT - GRID) : snake->cur_pos.y;
	snake->cur_pos.y = snake->cur_pos.y >= HEIGHT ? 0 : snake->cur_pos.y;
}

void		move_snake_body(t_snake *body, t_point new_pos)
{
	body->old_pos = body->cur_pos;
	body->cur_pos = new_pos;
}

void		move_snake_head(t_snake *snake, int move)
{
	snake->old_pos = snake->cur_pos;
	if (move == KEY_RIGHT || move == KEY_D)
		snake->cur_pos.x += GRID;
	else if (move == KEY_LEFT || move == KEY_A)
		snake->cur_pos.x -= GRID;
	else if (move == KEY_UP || move == KEY_W)
		snake->cur_pos.y -= GRID;
	else if (move == KEY_DOWN || move == KEY_S)
		snake->cur_pos.y += GRID;	
}

void		move_snake(t_mlx *mlx, int player)
{
	t_snake *snake;

	snake = SNAKEHEAD[player];
	move_snake_head(snake, KEYCONF[player]->move);
	if (GAME->players == 2 && check_collision_player(mlx, player)) /* HEAD-ON COLLISION LOOKS WIERD */
		game_over(mlx, player);
	if (GAME->map == KEY_1)
		no_sides(snake);
	else if (GAME->map == KEY_2 && check_sides_collision(SNAKEHEAD[player]))
		game_over(mlx, player);
	else if (GAME->map == KEY_3)
	{
		map3_sides(snake);
		if (check_map3_collision(SNAKEHEAD[player]))
			game_over(mlx, player);
	}
	while (snake->next)
	{
		move_snake_body(snake->next, snake->old_pos);
		snake = snake->next;
		if (check_collision_body(SNAKEHEAD[player]->cur_pos, snake))
			game_over(mlx, player);
	}
	check_apple(mlx, player);
}
