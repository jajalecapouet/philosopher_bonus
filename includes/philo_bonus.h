/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:11:22 by njaros            #+#    #+#             */
/*   Updated: 2022/05/09 10:42:42 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct law
{
	int				philo_number;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				eat_number;
	int				usleep_val;
	sem_t			*write;
	sem_t			*forks;
	sem_t			*remaining;
	sem_t			*die;
	struct timeval	start;
	int				*pid_adr;
}	t_law;

typedef struct s_philo_data
{
	struct timeval	start;
	sem_t			*write;
	sem_t			*forks;
	sem_t			*die;
	sem_t			*remaining;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				eat_number;
	int				usleep_val;
}	t_data;

typedef struct s_time
{
	struct timeval	start;
	struct timeval	last_eat;
	struct timeval	current;
	t_data			*data;
	int				n;
}	t_time;

// Corps du programme

int		main(int ac, char **av);
int		philo_bonus(t_law *law);
void	philo_handler(t_data data, int n);
int		lets_fork_the_phils(t_law *law, pthread_t meal_counter);
int		je_mange(int n, t_time *tps, t_data *data);
int		j_ai_fini(t_data *data, t_time *tps, int n);
void	je_dors(int n, t_time *tps, t_data *data);
int		keskifou(sem_t *write, t_time *tps, int philo, char *str);
int		error(int err);

// Outils utiles

int		ms(struct timeval t1, struct timeval t2);
int		us(struct timeval t1, struct timeval t2);
void	init_time(t_time *tps, t_data *data, int n);

// Fonctions de mise en place

int		parsing(char **to_parse, t_law *to_fill);
int		init_sem(t_law *law);
void	data_builder(t_data *data, t_law *law);

// Fonctions de destruction

void	gordon_freeman(t_law *law);
void	destroy_semaphore(t_law *law);

// Fonctions de la libft

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);

#endif