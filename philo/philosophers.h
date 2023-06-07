/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:37:14 by rferrero          #+#    #+#             */
/*   Updated: 2023/06/07 15:08:13 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//  includes
//  printf()
# include <stdio.h>
//  malloc()  free()
# include <stdlib.h>
//  write()  usleep()
# include <unistd.h>
//  gettimeofday()
# include <sys/time.h>
//  pthread_create()  pthread_detach()  pthread_join()  pthread_mutex_init()
//  pthread_mutex_destroy()  pthread_mutex_lock()  pthread_mutex_unlock()
# include <pthread.h>

//  defines
# define TRUE 1
# define FALSE 0

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define WHITE "\001\033[0;97m\002"
# define LGREEN "\001\033[0;92m\002"
# define CYAN "\001\033[0;93m\002"
# define PURPLE "\001\033[0;34m\002"
# define ORANGE "\001\033[0;94m\002"
# define RED "\001\033[0;31m\002"

//  structs
typedef struct s_data
{
	int					total_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	int					meals_ate;
	int					*dead;
	long long			time_start;
	pthread_mutex_t		*death;
}	t_data;

typedef struct s_philos
{
	int					id;
	long long			time_last_meal;
	t_data				*data;
	pthread_t			thread;
	pthread_mutex_t		fork_left;
	pthread_mutex_t		*fork_right;
}	t_philos;

//  utils/ft_arg_check.c
int			arg_handler(int argc, char **argv);

//  utils/ft_free.c
void		free_handler(t_data *data, t_philos *philo);

//  utils/ft_init.c
void		init_handler(char **argv, t_data *data, t_philos *philo);

//  utils/ft_numbers.c
long int	ft_atol(char *argv);
int			is_int(char *argv);

//  utils/ft_print.c
void		print_status(t_philos *philo, char *status, char *colour);

//  utils/ft_routine.c
void		*philo_routine(void *philo);

//  utils/ft_thread.c
int			create_threads(t_data *data, t_philos *philo);

//  utils/ft_time.c
long long	ft_time(void);
void		ft_sleep(int miliseconds);

#endif