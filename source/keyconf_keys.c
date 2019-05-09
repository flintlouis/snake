/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyconf_keys.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 14:18:18 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/09 19:59:20 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

int			close_window(void *ptr)
{
	(void)ptr;
	exit(0);
	return (0);
}

static void	delete_snake(t_snake *snake)
{
	if (!snake)
		return ;
	delete_snake(snake->next);
	free(snake);
	snake = NULL;
}

static	void game_reset(t_mlx *mlx)
{
	int i;

	i = 0;
	free(KEYCONF);
	init_keyconf(mlx);
	delete_snake(SNAKEHEAD);
	init_snake(mlx);
	APPLE->on = 0;
}

int			release_key(int key, t_mlx *mlx)
{
	if (key == KEY_PLUS)
		add_snake_body(mlx);
	if (key == KEY_SPACE)
		game_reset(mlx);
	return (0);
}

int			press_key(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		close_window(NULL);
	if (key == KEY_RIGHT && KEYCONF->move != KEY_LEFT)
		KEYCONF->move = KEY_RIGHT;
	else if (key == KEY_LEFT && KEYCONF->move != KEY_RIGHT)
		KEYCONF->move = KEY_LEFT;
	else if (key == KEY_UP && KEYCONF->move != KEY_DOWN)
		KEYCONF->move = KEY_UP;
	else if (key == KEY_DOWN && KEYCONF->move != KEY_UP)
		KEYCONF->move = KEY_DOWN;
	return (0);
}
