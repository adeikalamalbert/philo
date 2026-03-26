/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadeikal <aadeikal@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:36:25 by aadeikal          #+#    #+#             */
/*   Updated: 2026/03/26 15:46:22 by aadeikal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				die;
	int				eat;
	int				sleepzzz;
	int				lastmeal;
	int				status;
	int				rounds;
	int				philonumber;
	int				fork;
	int				forks;
	int				*stop;
	int				*roundscompleted;
	pthread_mutex_t	*fork_m;
	pthread_mutex_t	*stop_m;
}					t_philo;

typedef struct s_args
{
	t_philo			*philo_current;
	t_philo			*philo_adjacent;
}					t_args;

/* -------------------------------- main.c ---------------------------------- */

int					ft_timestamp(void);

/* -------------------------------- init.c ---------------------------------- */

int					init(t_philo *philos, int *stop, int ac, char **av);
int					init_threads(pthread_t *th, int nbr, t_philo *philos);
void				rounds_args(t_philo *philos, int *roundscompleted,
						pthread_mutex_t *stm);
void				time_args(t_philo *philos, char **av);

/* -------------------------------- loop.c ---------------------------------- */

void				*loop(void *philo);
void				die(t_philo *philo);
void				eat(t_philo *philo, t_philo *other);
void				sleepzzz(t_philo *philo);
void				think(t_philo *philo, t_philo *other);

/* ----------------------------- loop_utils.c ------------------------------- */

void				ft_usleep(int time_to_wait, t_philo *philo);
void				ft_takefork(t_philo *philo, t_philo *other);
void				ft_leavefork(t_philo *philo, t_philo *other);
void				rounds(t_philo *philo);

/* -------------------------------- utils.c --------------------------------- */

int					ft_printerror(char *s);
void				ft_printexec(int time, char *message, t_philo *philo);
void				ft_free(t_philo *philos, int nbr);
int					ft_close(t_philo *philos, pthread_t *threads, int nbr);
int					get_stop(t_philo *philo);

/* ------------------------------ minilibft.c ------------------------------- */

size_t				ft_strlen(const char *str);
int					ft_atoi(const char *str);
int					ft_isspace(int c);
void				ft_putstr_fd(char *s, int fd);

#endif
