/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_snake.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/09 22:17:52 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/26 17:10:39 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

static int check_map3_collision(t_snake *snake_head)
{
	if ((snake_head->cur_pos.x < GRID && ((snake_head->cur_pos.y >= 0 && snake_head->cur_pos.y <= 140) || (snake_head->cur_pos.y >= 240 && snake_head->cur_pos.y <= HEIGHT))) ||
	(snake_head->cur_pos.x >= WIDTH - GRID && ((snake_head->cur_pos.y >= 0 && snake_head->cur_pos.y <= 140) || (snake_head->cur_pos.y >= 240 && snake_head->cur_pos.y <= HEIGHT))) ||
	(snake_head->cur_pos.y < GRID && ((snake_head->cur_pos.x >= 0 && snake_head->cur_pos.x <= 240) || (snake_head->cur_pos.x >= 340 && snake_head->cur_pos.x <= WIDTH))) ||
	(snake_head->cur_pos.y >= HEIGHT - GRID && ((snake_head->cur_pos.x >= 0 && snake_head->cur_pos.x <= 240) || (snake_head->cur_pos.x >= 340 && snake_head->cur_pos.x <= WIDTH))) ||
	(snake_head->cur_pos.x == 240 && (snake_head->cur_pos.y >= 140 && snake_head->cur_pos.y <= 240)) || (snake_head->cur_pos.x == 340 && (snake_head->cur_pos.y >= 140 && snake_head->cur_pos.y <= 240)))
		return (1);
	return (0);
}

static void map3_sides(t_snake *snake)
{
	snake->cur_pos.x = snake->cur_pos.x < 0 && (snake->cur_pos.y >= 150 && snake->cur_pos.y <= 230) ? (WIDTH - GRID) : snake->cur_pos.x;
	snake->cur_pos.x = snake->cur_pos.x >= WIDTH && (snake->cur_pos.y >= 150 && snake->cur_pos.y <= 230) ? 0 : snake->cur_pos.x;
	snake->cur_pos.y = snake->cur_pos.y < 0 && (snake->cur_pos.x >= 250 && snake->cur_pos.x <= 330) ? (HEIGHT - GRID) : snake->cur_pos.y;
	snake->cur_pos.y = snake->cur_pos.y >= HEIGHT && (snake->cur_pos.x >= 250 && snake->cur_pos.x <= 330) ? 0 : snake->cur_pos.y;
}

static int check_sides_collision(t_snake *snake_head)
{
	if (snake_head->cur_pos.x >= WIDTH - GRID || snake_head->cur_pos.y >= HEIGHT - GRID
	|| snake_head->cur_pos.x < GRID || snake_head->cur_pos.y < GRID)
		return (1);
	return (0);
}

void no_sides(t_snake *snake)
{
	snake->cur_pos.x = snake->cur_pos.x >= WIDTH ? 0 : snake->cur_pos.x;
	snake->cur_pos.x = snake->cur_pos.x < 0 ? (WIDTH - GRID) : snake->cur_pos.x;
	snake->cur_pos.y = snake->cur_pos.y < 0 ? (HEIGHT - GRID) : snake->cur_pos.y;
	snake->cur_pos.y = snake->cur_pos.y >= HEIGHT ? 0 : snake->cur_pos.y;
}

int check_collision(t_snake *snake_head, t_snake *body)
{
	if (!body)
		return (0);
	if (snake_head->cur_pos.x == body->cur_pos.x && snake_head->cur_pos.y == body->cur_pos.y)
		return (1);
	return (0);
}

static int check_collision_player(t_mlx *mlx, int player)
{
	int opponent;
	t_snake *opponent_snake;

	opponent = (player + 1) % 2;
	opponent_snake = SNAKEHEAD[opponent];
	while (opponent_snake)
	{
		if (check_collision(SNAKEHEAD[player], opponent_snake))
			return (1);
		opponent_snake = opponent_snake->next;
	}
	return (0);
}

void	move_snake_body(t_snake *body, t_point new_pos)
{
	body->old_pos = body->cur_pos;
	body->cur_pos = new_pos;
}

void	move_snake_head(t_snake *snake, int move)
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

static void game_over(t_mlx *mlx, int player)
{
	char *snakes[2] = {"Yellow", "Green"};

	if (GAME->players == 1)
		printf("OUCH! You crashed.\n");
	else
		printf("%s wins!\n", snakes[(player + 1) % 2]);
	GAME->game_over = 1;
}

void	move_snake(t_mlx *mlx, int player)
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
		if (check_collision(SNAKEHEAD[player], snake))
			game_over(mlx, player);
	}
	check_apple(mlx, player);
}
