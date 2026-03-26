/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadeikal <aadeikal@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:35:47 by aadeikal          #+#    #+#             */
/*   Updated: 2026/03/26 15:45:36 by aadeikal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("%d %d %s\n", time, philo->id, message);
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

int	get_stop(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(philo->stop_m);
	res = *(philo->stop);
	pthread_mutex_unlock(philo->stop_m);
	return (res);
}
