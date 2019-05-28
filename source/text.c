/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   text.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/27 15:02:38 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/28 19:02:34 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"
#include <stdlib.h>

void	score(t_mlx *mlx)
{
	char		*score;
	static int	high_score; /* <---- */

	if (KEYCONF[0]->score > high_score) /* <---- */
		high_score = KEYCONF[0]->score; /* <---- */
	score = ft_itoa(high_score); /* <---- */ //score = ft_itoa(KEYCONF[0]->score);
	mlx_string_put(mlx->mlx, mlx->win, 20, 20, 0xffffff, score); /* <---- */
	free(score); /* <---- */
	score = ft_itoa(KEYCONF[0]->score);
	mlx_string_put(mlx->mlx, mlx->win, 560, 20, 0xffffff, score);
	free(score);
}

void	start_text(t_mlx *mlx)
{
	if (GAME->players == 1)
		mlx_string_put(mlx->mlx, mlx->win, 220, 100, 0xffffff, "GET A HIGHSCORE");
	else
		mlx_string_put(mlx->mlx, mlx->win, 200, 100, 0xffffff, "KILL THE OTHER PLAYER");
}
