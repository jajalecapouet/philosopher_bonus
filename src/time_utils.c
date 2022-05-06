/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:44:00 by njaros            #+#    #+#             */
/*   Updated: 2022/05/06 18:33:52 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ms(struct timeval t1, struct timeval t2)
{
	int	temps_ms;

	temps_ms = (t2.tv_sec - t1.tv_sec) * 1000;
	temps_ms += (t2.tv_usec - t1.tv_usec) / 1000;
	return (temps_ms);
}

int	us(struct timeval t1, struct timeval t2)
{
	int	temps_us;

	temps_us = (t2.tv_sec - t1.tv_sec) * 1000000;
	temps_us += (t2.tv_usec - t1.tv_usec);
	return (temps_us);
}

int	keskifou(sem_t *write, t_time *tps, int philo, char *str)
{
	int	time;

	sem_wait(write);
	gettimeofday(&tps->current, NULL);
	time = ms(tps->start, tps->current);
	printf("%d %d %s", time, philo, str);
	sem_post(write);
	return (0);
}

void	init_time(t_time *tps, t_law *law, int n)
{
	gettimeofday(&tps->current, NULL);
	gettimeofday(&tps->last_eat, NULL);
	tps->start = law->start;
	tps->law = law;
	tps->n = n;
	if (n % 2 == 1)
		usleep(law->philo_number * 100);
}
