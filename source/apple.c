/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   apple.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: FlintLouis <FlintLouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/09 22:08:34 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/05/10 00:26:21 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

void place_apple(t_mlx *mlx)
{
	if (!APPLE->on)
		APPLE->pos = random_pixel();
	if (APPLE->pos.x == WIDTH)
		APPLE->pos.x -= GRID;
	if (APPLE->pos.y == HEIGHT)
		APPLE->pos.y -= GRID;
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
		KEYCONF->score += 5;
		while (grow < 3)
		{
			add_snake_body(mlx, player);
			grow++;
		}
		KEYCONF->growth = (KEYCONF->growth + 1) % 4;
		if (KEYCONF->growth == 3 && KEYCONF->speed != 0)
			KEYCONF->speed -= .5;
	}
}