/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_snake.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/09 22:17:52 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/10 00:26:27 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

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

static void move_head(t_mlx *mlx, t_snake *snake)
{
		if (KEYCONF->move == KEY_RIGHT)
		{
			snake->cur_pos.x += GRID;
			snake->cur_pos.x = snake->cur_pos.x == WIDTH ? 0 : snake->cur_pos.x;			
		}
		else if (KEYCONF->move == KEY_LEFT)
		{
			snake->cur_pos.x -= GRID;
			snake->cur_pos.x= snake->cur_pos.x < 0 ? (WIDTH - GRID) : snake->cur_pos.x;
		}
		else if (KEYCONF->move == KEY_UP)
		{
			snake->cur_pos.y -= GRID;
			snake->cur_pos.y = snake->cur_pos.y < 0 ? (HEIGHT - GRID) : snake->cur_pos.y;
		}
		else if (KEYCONF->move == KEY_DOWN)
		{
			snake->cur_pos.y += GRID;
			snake->cur_pos.y = snake->cur_pos.y == HEIGHT ? 0 : snake->cur_pos.y;
		}
}

void	move_snake(t_mlx *mlx, int player)
{
	static double i;
	t_snake *snake;

	if (i == KEYCONF->speed)
	{	
		snake = SNAKEHEAD[player];
		snake->old_pos = snake->cur_pos;
		move_head(mlx, snake);
		while (snake->next)
		{
			move_snake_body(snake->next, snake->old_pos);
			snake = snake->next;
			if (check_collision(SNAKEHEAD[player], snake))
			{
				ft_putendl("OUCH!!!");
				KEYCONF->game_over = 1;
			}
		}
		check_apple(mlx, player);
		i = 0;
	}
	else
		i += .5;
}
