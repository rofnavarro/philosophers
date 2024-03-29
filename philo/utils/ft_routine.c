/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:57:38 by rferrero          #+#    #+#             */
/*   Updated: 2023/06/24 20:22:06 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	get_fork(t_philos *philo, int fork)
{
	pthread_mutex_lock(&philo->fork[fork].fork_mutex);
	if (philo->fork[fork].fork)
		philo->fork[fork].fork = 0;
	else
		pthread_mutex_unlock(&philo->fork[fork].fork_mutex);
}

static void	return_fork(t_philos *philo, int fork)
{
	philo->fork[fork].fork = 1;
	pthread_mutex_unlock(&philo->fork[fork].fork_mutex);
}

int	ft_eating(t_philos *philo)
{
	int		fork1;
	int		fork2;

	fork1 = (philo->id -1);
	fork2 = (philo->id);
	if (fork2 == philo->data.total_philos)
		fork2 = 0;
	get_fork(philo, fork1);
	if (check_if_died(philo))
		return (1);
	print_status(philo, "has taken a fork", LGREEN);
	if (only_one_philo(philo) == TRUE)
		return (1);
	get_fork(philo, fork2);
	if (check_if_died(philo))
		return (1);
	print_eating(philo);
	philo->time_last_meal = ft_time() - philo->data.start;
	philo->meals_ate++;
	psleep(philo, philo->data.time_to_eat);
	return_fork(philo, fork1);
	return_fork(philo, fork2);
	return (0);
}

void	ft_sleeping(t_philos *philo)
{
	print_status(philo, "is sleeping", CYAN);
	psleep(philo, philo->data.time_to_sleep);
}

void	ft_thinking(t_philos *philo)
{
	print_status(philo, "is thinking", WHITE);
}
