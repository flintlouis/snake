/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/10 17:20:34 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/20 13:45:48 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

void	ft_wait(int sec, long nsec)
{
	struct timespec tim, tim2;
	tim.tv_sec = sec;
	tim.tv_nsec = nsec;
	nanosleep(&tim, &tim2);
}

static long    ft_milsec(void)
{
    long				ns;
    time_t				s;
    struct timespec		spec;

    clock_gettime(CLOCK_REALTIME, &spec);
    s = spec.tv_sec;
    ns = spec.tv_nsec;
    return (s * 1000 + ns / 1000000);
}

long	time_between_frames(void)
{
	static long ph_ms;
	long dms;
	
	if (ph_ms == 0)
		ph_ms = ft_milsec();
	dms = ft_milsec() - ph_ms;
	ph_ms = ft_milsec();
	return (dms);
}