/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:26:22 by njaros            #+#    #+#             */
/*   Updated: 2022/05/09 10:26:24 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	r;
	int		sign;

	r = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] == '\t') || (nptr[i] == '\n') || (nptr[i] == '\v')
		|| (nptr[i] == '\f') || (nptr[i] == '\r') || (nptr[i] == ' '))
		i++;
	if ((nptr[i] == '-') || (nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		r = 10 * r;
		r = r + (nptr[i] - '0');
		i++;
	}
	return ((int)sign * r);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}
