/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:29 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/15 13:25:44 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(int last, t_philo philo)
{
	if (philo.parameters->check_meal == 1
		&& philo.iteration_number == philo.parameters->maximum_iterations
		&& last == philo.parameters->num_of_philos - 1)
		return (ft_usleep(300, &philo));
	return (0);
}

int	check_death(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->parameters->death);
	time = get_time() - philo->meal;
	if (time >= philo->parameters->time_to_die && !philo->parameters->over)
	{
		pthread_mutex_unlock(philo->parameters->death);
		pthread_mutex_lock(philo->parameters->print_m);
		printf("%ldms Philosopher %d died\n",
			get_time() - philo->thread_start, philo->id);
		philo->parameters->over = 1;
		philo->dead = 1;
		pthread_mutex_unlock(philo->parameters->print_m);
		return (1);
	}
	pthread_mutex_unlock(philo->parameters->death);
	return (0);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(int time, t_philo *philo)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (philo->parameters->over)
			return (1);
		usleep(150);
	}
	return (1);
}

void	print_action(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->parameters->death);
	pthread_mutex_lock(philo->parameters->print_m);
	if (philo->parameters->over)
	{
		pthread_mutex_unlock(philo->parameters->death);
		pthread_mutex_unlock(philo->parameters->print_m);
		return ;
	}
	printf("%ldms %d %s\n", get_time() - philo->thread_start, philo->id, str);
	pthread_mutex_unlock(philo->parameters->death);
	pthread_mutex_unlock(philo->parameters->print_m);
}
