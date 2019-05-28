/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:46:58 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/28 18:55:27 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"


void    game_over(t_mlx *mlx, int player)
{
	char *snakes[2] = {"Yellow", "Green"};

	if (GAME->players == 1)
		printf("OUCH! You crashed.\n");
	else
		printf("%s wins!\n", snakes[(player + 1) % 2]);
	GAME->game_over = 1;
}

int     check_map3_collision(t_snake *snake_head)
{
	if ((snake_head->cur_pos.x < GRID && ((snake_head->cur_pos.y >= 0 && snake_head->cur_pos.y <= 140) || (snake_head->cur_pos.y >= 240 && snake_head->cur_pos.y <= HEIGHT))) ||
	(snake_head->cur_pos.x >= WIDTH - GRID && ((snake_head->cur_pos.y >= 0 && snake_head->cur_pos.y <= 140) || (snake_head->cur_pos.y >= 240 && snake_head->cur_pos.y <= HEIGHT))) ||
	(snake_head->cur_pos.y < GRID && ((snake_head->cur_pos.x >= 0 && snake_head->cur_pos.x <= 240) || (snake_head->cur_pos.x >= 340 && snake_head->cur_pos.x <= WIDTH))) ||
	(snake_head->cur_pos.y >= HEIGHT - GRID && ((snake_head->cur_pos.x >= 0 && snake_head->cur_pos.x <= 240) || (snake_head->cur_pos.x >= 340 && snake_head->cur_pos.x <= WIDTH))) ||
	(snake_head->cur_pos.x == 240 && (snake_head->cur_pos.y >= 140 && snake_head->cur_pos.y <= 240)) || (snake_head->cur_pos.x == 340 && (snake_head->cur_pos.y >= 140 && snake_head->cur_pos.y <= 240)))
		return (1);
	return (0);
}

int     check_sides_collision(t_snake *snake_head)
{
	if (snake_head->cur_pos.x >= WIDTH - GRID || snake_head->cur_pos.y >= HEIGHT - GRID
	|| snake_head->cur_pos.x < GRID || snake_head->cur_pos.y < GRID)
		return (1);
	return (0);
}

int     check_collision_body(t_snake *snake_head, t_snake *body)
{
	if (!body)
		return (0);
	if (snake_head->cur_pos.x == body->cur_pos.x && snake_head->cur_pos.y == body->cur_pos.y)
		return (1);
	return (0);
}

int     check_collision_player(t_mlx *mlx, int player)
{
	int opponent;
	t_snake *opponent_snake;

	opponent = (player + 1) % 2;
	opponent_snake = SNAKEHEAD[opponent];
	while (opponent_snake)
	{
		if (check_collision_body(SNAKEHEAD[player], opponent_snake))
			return (1);
		opponent_snake = opponent_snake->next;
	}
	return (0);
}
