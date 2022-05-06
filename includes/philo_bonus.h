
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
}	law;

// Corps du programme

int		error(int err);
int		main(int ac, char **av);
void	fork_handler(void);

// Fonctions de mise en place

int		parsing(char **to_parse, law *to_fill);
sem_t	**init_semafork(int size, char **names);
char	**init_fork_names(int size);

// Fonctions de destruction

int		freestyle(char **strs, int err);

// Fonctions de la libft

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
void	ft_strcat(char *dest, char *src);
size_t	ft_strlen(const char *str);
char	*ft_itoa(int n);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);

#endif