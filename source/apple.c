/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   apple.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/09 22:08:34 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/26 16:04:53 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

void place_apple(t_mlx *mlx)
{
	if (!APPLE->on)
		APPLE->pos = random_pixel();
	if (GAME->map == KEY_3)
	{
		while ((APPLE->pos.x == 240 && ((APPLE->pos.y >= 140 && APPLE->pos.y <= 240)))
		|| (APPLE->pos.x == 340 && ((APPLE->pos.y >= 140 && APPLE->pos.y <= 240))))
			APPLE->pos = random_pixel();
	}
	put_square(mlx, APPLE->pos, (t_colour){0xB2, 0x22, 0x22});
	APPLE->on = 1;
}

void check_apple(t_mlx *mlx, int player)
{
	int grow;

	grow = 0;
	if (SNAKEHEAD[player]->cur_pos.x == APPLE->pos.x && SNAKEHEAD[player]->cur_pos.y == APPLE->pos.y)
	{
		APPLE->on = 0;
		KEYCONF[player]->score += 5;
		while (grow < 3)
		{
			add_snake_body(SNAKEHEAD[player]);
			grow++;
		}
		if (GAME->players == 1 && KEYCONF[0]->speed > 18)
			KEYCONF[0]->speed -= 2;
	}
}
