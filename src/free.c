#include "philo_bonus.h"

int	freestyle(char **strs, int err)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
	return (err);
}