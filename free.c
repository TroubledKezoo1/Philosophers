/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 07:19:21 by ysarac            #+#    #+#             */
/*   Updated: 2024/05/20 23:10:27 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	table_free(t_table *table)
{
	philo_free(&table->first_philo);
}

void	philo_free(t_philo **root)
{
	t_philo	*current;
	t_philo	*next;

	if (*root == NULL)
		return ;
	current = *root;
	next = NULL;
	while (current != NULL)
	{
		next = current->right_philo;
		free(current->right_fork);
		free(current);
		if (next == *root)
			current = NULL;
		else
			current = next;
	}
	*root = NULL;
}

void	double_free(char **av)
{
	int	i;

	if (av != NULL)
	{
		i = 0;
		while (av[i])
		{
			free(av[i]);
			i++;
		}
		free(av);
	}
}

int	mutex_free(pthread_mutex_t *mutex)
{
	if (mutex != NULL)
	{
		if ((pthread_mutex_unlock(mutex) != 0)
			&& (pthread_mutex_destroy(mutex) != 0))
		{
			return (free(mutex), 0);
		}
		return (1);
	}
	return (0);
}
