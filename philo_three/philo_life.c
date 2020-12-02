/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecaudal <jecaudal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:55:01 by jecaudal          #+#    #+#             */
/*   Updated: 2020/12/02 10:46:26 by jecaudal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static t_bool	take_forks(t_list *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->forks);
	print_sem(get_time(philo->tt_start) / 1000, philo, EVENT_FORK);
	print_sem(get_time(philo->tt_start) / 1000, philo, EVENT_FORK);
	return (TRUE);
}

static t_bool	p_eat(t_list *philo)
{
	philo->alive = TRUE;
	philo->tt_starvation = get_curr_time() + philo->time_to_die * 1000;
	if (philo->to_eat > 0)
		philo->to_eat--;
	print_sem(get_time(philo->tt_start) / 1000, philo, EVENT_EAT);
	usleep(philo->time_to_eat * ONE_MILLISECOND);
	sem_post(philo->forks);
	sem_post(philo->forks);
	if (philo->to_eat == 0)
		return (FALSE);
	return (philo->alive);
}

static t_bool	p_sleep(t_list *philo)
{
	print_sem(get_time(philo->tt_start) / 1000, philo, EVENT_SLEEP);
	usleep(philo->time_to_sleep * ONE_MILLISECOND);
	return (philo->alive);
}

static t_bool	p_think(t_list *philo)
{
	print_sem(get_time(philo->tt_start) / 1000, philo, EVENT_THINK);
	if (philo->n_philo % 2)
		usleep(philo->time_to_sleep * 999);
	return (philo->alive);
}

void			*philo_life(void *philo)
{
	int						i;
	static t_actions_arr	arr[4] = {take_forks, p_eat, p_sleep, p_think};

	i = 0;
	while (arr[i](philo))
	{
		if (i == 3)
			i = 0;
		else
			i++;
	}
	exit(0);
	return (NULL);
}
