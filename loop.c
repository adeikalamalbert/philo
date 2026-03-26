/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadeikal <aadeikal@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:36:16 by aadeikal          #+#    #+#             */
/*   Updated: 2026/03/26 15:42:39 by aadeikal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*loop(void *arguments)
{
	t_args	*args;
	t_philo	*ph;

	args = (t_args *)arguments;
	ph = args->philo_current;
	if (ph->id % 2)
		usleep(3000);
	while (!get_stop(ph) && ph->rounds)
	{
		rounds(ph);
		die(ph);
		if (ph->status == 0 && !get_stop(ph))
			eat(ph, args->philo_adjacent);
		else if (ph->status == 1 && !get_stop(ph))
			sleepzzz(ph);
		else if (ph->status == 2 && !get_stop(ph))
			think(ph, args->philo_adjacent);
	}
	free(arguments);
	return (0);
}

void	die(t_philo *philo)
{
	pthread_mutex_lock(philo->stop_m);
	if (!*(philo->stop) && ft_timestamp() - philo->lastmeal > philo->die)
	{
		printf("%d %d died\n", ft_timestamp(), philo->id);
		*philo->stop = 1;
	}
	pthread_mutex_unlock(philo->stop_m);
}

void	eat(t_philo *philo, t_philo *other)
{
	if (get_stop(philo))
		return ;
	ft_printexec(ft_timestamp(), "is eating", philo);
	philo->lastmeal = ft_timestamp();
	ft_usleep(philo->eat, philo);
	ft_leavefork(philo, other);
	if (philo->rounds > 0)
		philo->rounds -= 1;
	philo->status = 1;
}

void	sleepzzz(t_philo *philo)
{
	if (get_stop(philo))
		return ;
	ft_printexec(ft_timestamp(), "is sleeping", philo);
	ft_usleep(philo->sleepzzz, philo);
	philo->status = 2;
}

void	think(t_philo *philo, t_philo *other)
{
	if (get_stop(philo) || get_stop(other))
		return ;
	ft_printexec(ft_timestamp(), "is thinking", philo);
	if (philo->philonumber == 1)
	{
		pthread_mutex_lock(philo->fork_m);
		ft_printexec(ft_timestamp(), "has taken a fork", philo);
		ft_usleep(philo->die * 2, philo);
		pthread_mutex_unlock(philo->fork_m);
		return ;
	}
	while (!get_stop(philo) && philo->forks < 2)
	{
		ft_takefork(philo, other);
		die(philo);
		if (philo->forks < 2)
			usleep(100);
	}
	philo->status = 0;
}
