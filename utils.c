#include "philosophers.h"

int	ft_printerror(char *s)
{
	ft_putstr_fd(s, 2);
	return (1);
}

void	ft_printexec(int time, char *message, t_philo *philo)
{
	pthread_mutex_lock(philo->stop_m);
	if (!*philo->stop)
		printf("%d %d %s\n", time, philo->ID, message);
	pthread_mutex_unlock(philo->stop_m);
}

void	ft_free(t_philo *philos, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
	{
		pthread_mutex_destroy(philos[i].fork_m);
		free(philos[i].fork_m);
	}
	free(philos);
}

int	ft_close(t_philo *philos, pthread_t *threads, int nbr)
{
	int	i;

	pthread_mutex_destroy(philos[0].stop_m);
	if (threads)
	{
		i = -1;
		while (++i < nbr)
			pthread_join(threads[i], NULL);
		free(threads);
	}
	if (philos)
		ft_free(philos, nbr);
	return (1);
}

int	ft_timestamp(void)
{
    struct timeval	time;
    static long long start_time = 0;
    long long current_time;

    gettimeofday(&time, NULL);
    current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);    
    if (start_time == 0)
        start_time = current_time;   
    return (current_time - start_time);
}

