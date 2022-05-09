/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:41:27 by njaros            #+#    #+#             */
/*   Updated: 2022/05/09 10:36:31 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_semaphore(t_law *law)
{
	sem_close(law->die);
	sem_close(law->write);
	sem_close(law->remaining);
	sem_close(law->forks);
	sem_unlink("/write");
	sem_unlink("/forks");
	sem_unlink("/remaining");
	sem_unlink("/die");
}

void	gordon_freeman(t_law *law)
{
	destroy_semaphore(law);
	free(law->pid_adr);
}
