/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:58:40 by ysarac            #+#    #+#             */
/*   Updated: 2024/04/30 16:32:40 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	print(t_philo *philo, char *str)
{
	if (pthread_mutex_lock(&philo->table->write) != 0
		&& pthread_mutex_lock(&philo->table->isdie) != 0)
		return (mutex_free(&philo->table->write));
	if (philo->table->dieis == 0)
		printf("%llu %d.Philo ::  %s\n", time_from_start(philo->table),
			philo->id, str);
	if (ft_strncmp(str, DIE, ft_strlen(str)) == 0)
		philo->table->dieis++;
	if (pthread_mutex_unlock(&philo->table->write) != 0
		&& pthread_mutex_unlock(&philo->table->isdie))
		return (mutex_free(&philo->table->write));
	return (1);
}

int	must_eating_check(t_table *table)
{
	t_philo	*iter;
	int		i;

	if (table->number_of_must_eat < 0)
		return (0);
	i = 1;
	iter = table->first_philo;
	while (i <= table->number_of_philo)
	{
		pthread_mutex_lock(&iter->count_eat);
		if (iter->eat_count < table->number_of_must_eat)
		{
			pthread_mutex_unlock(&iter->count_eat);
			return (0);
		}
		else
			pthread_mutex_unlock(&iter->count_eat);
		iter = iter->right_philo;
		i++;
	}
	return (1);
}

int	check_die(t_table *table)
{
	t_philo	*iter;

	iter = table->first_philo;
	while (1)
	{
		pthread_mutex_lock(&iter->eat_check);
		if ((current_time() - iter->last_eat) >= table->time_to_die)
		{
			print(iter, DIE);
			pthread_mutex_lock(&table->stop_flag);
			table->stop = 1;
			pthread_mutex_unlock(&table->stop_flag);
			pthread_mutex_unlock(&iter->eat_check);
			return (0);
		}
		else if (must_eating_check(table))
			break ;
		pthread_mutex_unlock(&iter->eat_check);
		iter = iter->right_philo;
	}
	return (1);
}

void	die_check(t_table *table)
{
	if (table->number_of_philo == 1)
		print(table->first_philo, DIE);
	if (!(check_die(table)))
		return ;
	pthread_mutex_lock(&table->stop_flag);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_flag);
}

void	destroyss(t_table *table)
{
	t_philo	*iter;
	int		i;

	i = 1;
	iter = table->first_philo;
	while (i <= table->number_of_philo)
	{
		pthread_mutex_destroy(iter->right_fork);
		pthread_mutex_destroy(&iter->eat_check);
		pthread_mutex_destroy(&iter->count_eat);
		iter = iter->right_philo;
		i++;
	}
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->eat_last);
	pthread_mutex_destroy(&table->stop_flag);
	pthread_mutex_destroy(&table->isdie);
}
