// /* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/08 15:47:01 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/08 16:11:11 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

int		main(int argc, char **argv)
{
	if (argc == 2)
		setup_snake(ft_atoi(argv[1]));
	return (0);
}
