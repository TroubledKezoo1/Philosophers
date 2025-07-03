/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:31:10 by ysarac            #+#    #+#             */
/*   Updated: 2024/05/20 23:33:22 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	philo_add(t_philo **root, int id, t_table *table)
{
	t_philo	*newphilo;

	newphilo = (t_philo *)malloc(sizeof(t_philo));
	if (!newphilo)
		return (printf("Philo Init Error "), philo_free(root), 0);
	newphilo->id = id;
	newphilo->table = table;
	newphilo->right_philo = newphilo;
	newphilo->left_philo = newphilo;
	newphilo->right_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (newphilo->right_fork == NULL)
		return (printf("Philo Right Fork Init Error"), free(newphilo),
			philo_free(root), 0);
	if (*root == NULL)
		*root = newphilo;
	else
	{
		(*root)->left_fork = newphilo->right_fork;
		newphilo->left_fork = (*root)->left_philo->right_fork;
		(*root)->left_philo->right_philo = newphilo;
		newphilo->left_philo = (*root)->left_philo;
		(*root)->left_philo = newphilo;
		newphilo->right_philo = *root;
	}
	return (1);
}

int	create_philo(t_table *table)
{
	int	i;

	i = 1;
	table->first_philo = NULL;
	while (i <= table->number_of_philo)
	{
		if (!philo_add(&table->first_philo, i, table))
			return (0);
		i++;
	}
	return (1);
}

int	init_mutexes(t_table *table)
{
	t_philo	*iter;
	int		i;

	iter = table->first_philo;
	i = 1;
	while (i <= table->number_of_philo)
	{
		pthread_mutex_init(iter->right_fork, NULL);
		pthread_mutex_init(&iter->eat_check, NULL);
		pthread_mutex_init(&iter->count_eat, NULL);
		iter->eat_count = 0;
		iter = iter->right_philo;
		i++;
	}
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->eat_last, NULL);
	pthread_mutex_init(&table->stop_flag, NULL);
	pthread_mutex_init(&table->isdie, NULL);
	return (1);
}

int	ft_initialize(t_table *table, char **av)
{
	table->number_of_philo = ft_atoi(av[0]);
	if (table->number_of_philo == 0)
		return (0);
	table->time_to_die = ft_atoi(av[1]);
	table->time_to_eat = ft_atoi(av[2]);
	table->time_to_sleap = ft_atoi(av[3]);
	table->number_of_must_eat = -1;
	if (av[4])
		table->number_of_must_eat = ft_atoi(av[4]);
	if (!create_philo(table))
		return (0);
	if (!init_mutexes(table))
		return (0);
	table->stop = 0;
	table->time = current_time();
	table->dieis = 0;
	return (1);
}

int	ft_start(t_table *table)
{
	if (table->number_of_philo == 1)
	{
		table->time = current_time();
		print(table->first_philo, TAKEN_FORK);
		time_from_start(table);
		time_usleep(table->time_to_die);
		print(table->first_philo, DIE);
		return (1);
	}
	else if (table->number_of_philo > 1)
		if (!start_thread(table))
			return (0);
	return (1);
}
