/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadeikal <aadeikal@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:36:13 by aadeikal          #+#    #+#             */
/*   Updated: 2026/03/26 15:41:55 by aadeikal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(int time_to_wait, t_philo *philo)
{
	int	start;

	start = ft_timestamp();
	while (!get_stop(philo) && ft_timestamp() - start < time_to_wait)
	{
		die(philo);
		usleep(200);
	}
}

static void	lock_and_take(t_philo *philo, t_philo *target)
{
	pthread_mutex_lock(target->fork_m);
	if (target->fork && !get_stop(philo))
	{
		ft_printexec(ft_timestamp(), "has taken a fork", philo);
		target->fork = 0;
		philo->forks += 1;
	}
	pthread_mutex_unlock(target->fork_m);
}

void	ft_takefork(t_philo *philo, t_philo *other)
{
	if (get_stop(philo) || get_stop(other))
		return ;
	if (philo->fork_m < other->fork_m)
	{
		lock_and_take(philo, philo);
		if (philo->forks < 2)
			lock_and_take(philo, other);
	}
	else
	{
		lock_and_take(philo, other);
		if (philo->forks < 2)
			lock_and_take(philo, philo);
	}
}

void	ft_leavefork(t_philo *philo, t_philo *other)
{
	if (get_stop(philo) || get_stop(other))
		return ;
	pthread_mutex_lock(philo->fork_m);
	philo->fork = 1;
	pthread_mutex_unlock(philo->fork_m);
	pthread_mutex_lock(other->fork_m);
	other->fork = 1;
	pthread_mutex_unlock(other->fork_m);
	philo->forks = 0;
}

void	rounds(t_philo *philo)
{
	if (philo->rounds < 0)
		return ;
	if (!philo->rounds)
	{
		pthread_mutex_lock(philo->stop_m);
		*philo->roundscompleted += 1;
		if (*philo->roundscompleted >= philo->philonumber)
			*philo->stop = 1;
		pthread_mutex_unlock(philo->stop_m);
	}
}
