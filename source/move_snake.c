/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_snake.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/09 22:17:52 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/10 18:43:44 by fhignett      ########   odam.nl         */
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

static void	move_snake_body(t_snake *body, t_point new_pos)
{
	body->old_pos = body->cur_pos;
	body->cur_pos = new_pos;
}

static void move_snake_head(t_mlx *mlx, t_snake *snake)
{
		if (KEYCONF->move == KEY_RIGHT)
			snake->cur_pos.x += GRID;
		else if (KEYCONF->move == KEY_LEFT)
			snake->cur_pos.x -= GRID;
		else if (KEYCONF->move == KEY_UP)
			snake->cur_pos.y -= GRID;
		else if (KEYCONF->move == KEY_DOWN)
			snake->cur_pos.y += GRID;
}

static void game_over(t_mlx *mlx)
{
	ft_putendl("OUCH!!!");
	KEYCONF->game_over = 1;
}

void	move_snake(t_mlx *mlx, int player)
{
	t_snake *snake;

	snake = SNAKEHEAD[player];
	snake->old_pos = snake->cur_pos;
	move_snake_head(mlx, snake);
	// no_sides(snake); /* CAN PASS THROUGH SIDES */ 
	while (snake->next)
	{
		move_snake_body(snake->next, snake->old_pos);
		snake = snake->next;
		if (check_collision(SNAKEHEAD[player], snake))
			game_over(mlx);
	}
	if (check_sides_collision(SNAKEHEAD[player])) /* CAN'T PASS THROUGH SIDES */
		game_over(mlx);
	check_apple(mlx, player);
}
