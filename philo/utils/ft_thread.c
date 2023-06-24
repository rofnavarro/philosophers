/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:49:18 by rferrero          #+#    #+#             */
/*   Updated: 2023/06/24 00:07:36 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	*philo_r(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	if (!(philo->id % 2))
		usleep(10000);
	while (is_dead(philo) == FALSE)
	{
		if (ft_eating(philo))
			return (NULL);
		if (philo->data->max_meals != -1 && \
			philo->meals_ate == philo->data->max_meals || is_dead(philo) == TRUE)
			break ;
		ft_sleeping(philo);
		if (is_dead(philo))
			return (NULL);
		ft_thinking(philo);
		if (philo->data->total_philos % 2)
			usleep(2000);
	}
	return (NULL);
}

int	create_threads(t_philos *philo)
{
	int				i;
	pthread_mutex_t	print;

	pthread_mutex_init(&print, NULL);
	philo->data->start = ft_time();
	i = -1;
	while (++i < philo->data->total_philos)
		philo[i].print = &print;
	i = -1;
	while (++i < philo->data->total_philos)
	{
		if (pthread_create(&(philo[i].thread), NULL, &philo_r, &philo[i]) != 0)
			return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < philo->data->total_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
