#include "philosophers.h"

int	main(int ac, char **av)
{
    t_philo			*philos;
    pthread_t		*threads;
    pthread_mutex_t	stop_m;
    int				stop;
    int				rounds_completed;
    int				nb_philos;

    stop = 0;
    rounds_completed = 0;
    if (ac < 5 || ac > 6 || ft_atoi(av[1]) <= 0)
        return (ft_printerror("Incorrect or wrong number of arguments..."));
    nb_philos = ft_atoi(av[1]);
    pthread_mutex_init(&stop_m, NULL);
    philos = malloc(nb_philos * sizeof(t_philo));
    if (!philos || init(philos, &stop, ac, av))
        return (ft_close(philos, NULL, nb_philos));
    time_args(philos, av);
    rounds_args(philos, &rounds_completed, &stop_m);
    threads = malloc(nb_philos * sizeof(pthread_t));
    if (!threads || init_threads(threads, nb_philos, philos))
        return (ft_close(philos, threads, nb_philos));
    return (ft_close(philos, threads, nb_philos) * 0);
}
