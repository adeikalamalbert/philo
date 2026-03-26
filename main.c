/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadeikal <aadeikal@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:36:18 by aadeikal          #+#    #+#             */
/*   Updated: 2026/03/26 16:28:50 by aadeikal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_timestamp(void)
{
	struct timeval		time;
	static long long	start_time = 0;
	long long			current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (start_time == 0)
		start_time = current_time;
	return (current_time - start_time);
}

int	main(int ac, char **av)
{
	t_philo			*p;
	pthread_t		*t;
	pthread_mutex_t	m;
	int				v[2];
	int				n;

	v[0] = 0;
	v[1] = 0;
	if (ac < 5 || ac > 6 || ft_atoi(av[1]) <= 0)
		return (ft_printerror("Incorrect or wrong number of arguments..."));
	n = ft_atoi(av[1]);
	pthread_mutex_init(&m, NULL);
	p = malloc(n * sizeof(t_philo));
	if (!p || init(p, &v[0], ac, av))
		return (pthread_mutex_destroy(&m), ft_close(p, NULL, n));
	time_args(p, av);
	rounds_args(p, &v[1], &m);
	t = malloc(n * sizeof(pthread_t));
	if (!t || init_threads(t, n, p))
		return (ft_close(p, t, n), pthread_mutex_destroy(&m), 1);
	ft_close(p, t, n);
	pthread_mutex_destroy(&m);
	return (0);
}
