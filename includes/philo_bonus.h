/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:11:22 by njaros            #+#    #+#             */
/*   Updated: 2022/05/06 18:37:04 by njaros           ###   ########lyon.fr   */
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
}	t_law;

typedef	struct s_time
{
	struct timeval	start;
	struct timeval	last_eat;
	struct timeval	current;
	t_law			*law;
	int				n;
}	t_time;


// Corps du programme

int		main(int ac, char **av);
int		philo_bonus(t_law law);
void	philo_handler(t_law law, int n);
int		lets_fork_the_phils(t_law law);
int		je_mange(int n, t_time *tps, t_law *law);
int		j_ai_fini(t_law *law, t_time *tps, int n);
void	je_dors(int n, t_time *tps, t_law *law);
int		keskifou(sem_t *write, t_time *tps, int philo, char *str);
int		error(int err);

// Outils utiles

int		ms(struct timeval t1, struct timeval t2);
int		us(struct timeval t1, struct timeval t2);
void	init_time(t_time *tps, t_law *law, int n);

// Fonctions de mise en place

int		parsing(char **to_parse, t_law *to_fill);
int		init_sem(t_law *law);

// Fonctions de destruction

// Fonctions de la libft

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
void	ft_strcat(char *dest, char *src);
size_t	ft_strlen(const char *str);
char	*ft_itoa(int n);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);

#endif