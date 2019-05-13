/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_snake.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/09 22:17:52 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/13 19:37:18 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

static int check_sides_collision(t_snake *snake_head)
{
	if (snake_head->cur_pos.x == WIDTH - GRID || snake_head->cur_pos.y == HEIGHT - GRID
	|| snake_head->cur_pos.x < GRID || snake_head->cur_pos.y < GRID)
		return (1);
	return (0);
}

static void no_sides(t_snake *snake)
{
	snake->cur_pos.x = snake->cur_pos.x == WIDTH ? 0 : snake->cur_pos.x;
	snake->cur_pos.x= snake->cur_pos.x < 0 ? (WIDTH - GRID) : snake->cur_pos.x;
	snake->cur_pos.y = snake->cur_pos.y < 0 ? (HEIGHT - GRID) : snake->cur_pos.y;
	snake->cur_pos.y = snake->cur_pos.y == HEIGHT ? 0 : snake->cur_pos.y;
}

static int check_collision(t_snake *snake_head, t_snake *body)
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
	if (mlx->players != 2)
		return (0);
	opponent_snake = SNAKEHEAD[opponent];
	while (opponent_snake)
	{
		if (SNAKEHEAD[player]->cur_pos.x == opponent_snake->cur_pos.x && SNAKEHEAD[player]->cur_pos.y == opponent_snake->cur_pos.y)
			return (1);
		opponent_snake = opponent_snake->next;
	}
	return (0);
}

static void	move_snake_body(t_snake *body, t_point new_pos)
{
	body->old_pos = body->cur_pos;
	body->cur_pos = new_pos;
}

static void move_snake_head(t_mlx *mlx, t_snake *snake, int player)
{
	if (KEYCONF[player]->move == KEY_RIGHT || KEYCONF[player]->move == KEY_D)
		snake->cur_pos.x += GRID;
	else if (KEYCONF[player]->move == KEY_LEFT || KEYCONF[player]->move == KEY_A)
		snake->cur_pos.x -= GRID;
	else if (KEYCONF[player]->move == KEY_UP || KEYCONF[player]->move == KEY_W)
		snake->cur_pos.y -= GRID;
	else if (KEYCONF[player]->move == KEY_DOWN || KEYCONF[player]->move == KEY_S)
		snake->cur_pos.y += GRID;
}

static void game_over(t_mlx *mlx, int player)
{
	ft_putendl("OUCH!!!");
	KEYCONF[player]->game_over = 1;
}

void	move_snake(t_mlx *mlx, int player)
{
	t_snake *snake;

	snake = SNAKEHEAD[player];
	snake->old_pos = snake->cur_pos;
	move_snake_head(mlx, snake, player);
	if (check_collision_player(mlx, player)) /* HEAD ON COLLISION LOOKS WIERD */
		game_over(mlx, player);
	no_sides(snake); /* CAN PASS THROUGH SIDES */
	while (snake->next)
	{
		move_snake_body(snake->next, snake->old_pos);
		snake = snake->next;
		if (check_collision(SNAKEHEAD[player], snake))
			game_over(mlx, player);
	}
	// if (check_sides_collision(SNAKEHEAD[player])) /* CAN'T PASS THROUGH SIDES */
		// game_over(mlx, player);
	check_apple(mlx, player);
}
