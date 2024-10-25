/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:03:31 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/15 16:13:40 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	print_action("has taken left fork", philo);
	print_action("has taken right fork", philo);
	philo->meal = get_time();
	print_action("is eating", philo);
	ft_usleep(philo->parameters->time_to_eat, philo);
	philo->iteration_number++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_chill(t_philo *philo)
{
	print_action("is sleeping", philo);
	ft_usleep(philo->parameters->time_to_sleep, philo);
	print_action("is thinking", philo);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->parameters->ready)
		continue ;
	if (philo->parameters->num_of_philos == 1)
	{
		usleep(philo->parameters->time_to_die);
		return (NULL);
	}
	if (philo->id & 1)
		ft_usleep(philo->parameters->time_to_eat * 0.9 + 1, philo);
	while (!philo->parameters->over)
	{
		if (!philo->parameters->check_meal
			|| philo->iteration_number < philo->parameters->maximum_iterations)
		{
			eat_routine(philo);
			ft_chill(philo);
		}
	}
	return (NULL);
}
