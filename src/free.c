/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:41:27 by njaros            #+#    #+#             */
/*   Updated: 2022/05/09 13:03:17 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_semaphore(void)
{
	sem_unlink("/write");
	sem_unlink("/forks");
	sem_unlink("/remaining");
	sem_unlink("/die");
}

void	gordon_freeman(t_law *law)
{
	destroy_semaphore();
	free(law->pid_adr);
}
