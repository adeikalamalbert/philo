#include "philosophers.h"

int	init(t_philo *philos, int *stop, int ac, char **av)
{
    int	i;
    int	goal;
    int	nb_philosophers;

    goal = -1;
    if (ac == 6)
        goal = ft_atoi(av[5]);    
    nb_philosophers = ft_atoi(av[1]);
    i = 0;
    while (i < nb_philosophers)
    {
        philos[i].ID = i + 1;
        philos[i].status = 2;
        philos[i].rounds = goal;
        philos[i].philo_number = nb_philosophers;
        philos[i].fork = 1;
        philos[i].forks = 0;
        philos[i].stop = stop;
        philos[i].fork_m = malloc(sizeof(pthread_mutex_t));
        if (!philos[i].fork_m)
            return (1);
        pthread_mutex_init(philos[i].fork_m, NULL);
        i++;
    }
    return (0);
}

int	init_threads(pthread_t *th, int nbr, t_philo *philos)
{
    int		i;
    t_args	*args;

    i = 0;
    while (i < nbr)
    {
        args = malloc(sizeof(t_args));
        if (!args)
            return (1);
        args->philo_current = &philos[i];
        if (i == 0)
            args->philo_adjacent = &philos[nbr - 1];
        else
            args->philo_adjacent = &philos[i - 1];
        if (pthread_create(&th[i], NULL, loop, (void *) args) != 0)
            return (1);
        i++;
    }
    return (0);
}

void	time_args(t_philo *philos, char **av)
{
    int	i;
    int	nb_philosophers;
    int	time_to_die;
    int	time_to_eat;
    int	time_to_sleep;
    int	start_time;

    nb_philosophers = ft_atoi(av[1]);
    time_to_die = ft_atoi(av[2]);
    time_to_eat = ft_atoi(av[3]);
    time_to_sleep = ft_atoi(av[4]);
    
    start_time = ft_timestamp();
    i = 0;
    while (i < nb_philosophers)
    {
        philos[i].die = time_to_die;
        philos[i].eat = time_to_eat;
        philos[i].sleep_zzz = time_to_sleep;
        philos[i].last_meal = start_time;
        i++;
    }
}

void	rounds_args(t_philo *philos, int *rounds_completed, pthread_mutex_t *stm)
{
    int	i;
    int	total_philos;

    total_philos = philos[0].philo_number;
    i = 0;
    while (i < total_philos)
    {
        philos[i].rounds_completed = rounds_completed;
        philos[i].stop_m = stm;
        i++;
    }
}
