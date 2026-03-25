#include "philosophers.h"

void	*loop(void *arguments)
{
    t_args	*args;
    t_philo	*ph;

    args = (t_args *)arguments;
    ph = args->philo_current;
    if (ph->ID % 2)
        usleep(3000);
    while (!*(ph->stop) && ph->rounds)
    {
        rounds(ph);
        die(ph);
        if (ph->status == 0 && !*(ph->stop))
            eat(ph, args->philo_adjacent);
        else if (ph->status == 1 && !*(ph->stop))
            sleep_zzz(ph);
        else if (ph->status == 2 && !*(ph->stop))
            think(ph, args->philo_adjacent);
    }
    free(arguments);
    return (0);
}

void	die(t_philo *philo)
{
    pthread_mutex_lock(philo->stop_m);
    if (!*(philo->stop) && ft_timestamp() - philo->last_meal > philo->die)
    {
        printf("%d %d died\n", ft_timestamp(), philo->ID);
        *philo->stop = 1;
    }
    pthread_mutex_unlock(philo->stop_m);
}

void	eat(t_philo *philo, t_philo *other)
{
    if (*(philo->stop))
        return ;
    ft_printexec(ft_timestamp(), "is eating", philo);
    philo->last_meal = ft_timestamp();
    ft_usleep(philo->eat, philo);    
    ft_leavefork(philo, other);
    if (philo->rounds > 0)
        philo->rounds -= 1;
    philo->status = 1;
}

void	sleep_zzz(t_philo *philo)
{
    if (*(philo->stop))
        return ;
    ft_printexec(ft_timestamp(), "is sleeping", philo);
    ft_usleep(philo->sleep_zzz, philo);    
    philo->status = 2;
}

void	think(t_philo *philo, t_philo *other)
{
    if (*(philo->stop) || *(other->stop))
        return ;
    ft_printexec(ft_timestamp(), "is thinking", philo);
    if (philo->philo_number == 1)
    {
        pthread_mutex_lock(philo->fork_m);
        ft_printexec(ft_timestamp(), "has taken a fork", philo);
        ft_usleep(philo->die * 2, philo);
        pthread_mutex_unlock(philo->fork_m);
        return ;
    }
    while (!*(philo->stop) && philo->forks < 2)
    {
        ft_takefork(philo, other);
        die(philo);
        if (philo->forks < 2)
            usleep(100);
    }
    philo->status = 0;
}
