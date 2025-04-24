/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:16:21 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 20:16:50 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_env(t_env *a, t_env *b)
{
	t_env	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_env(t_env *env)
{
	int	swapped;
	int	i;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (env[i].key != NULL && env[i + 1].key != NULL)
		{
			if (compare_keys(env[i].key, env[i + 1].key) > 0)
			{
				swap_env(&env[i], &env[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
}

int	export_copy(t_env *dest, t_env *src)
{
	if (!src || !dest)
		return (EXIT_FAILURE);
	if (src->key)
	{
		dest->key = ft_strdup(src->key);
		if (!dest->key)
			return (EXIT_FAILURE);
	}
	else
		dest->key = NULL;
	if (src->value)
	{
		dest->value = ft_strdup(src->value);
		if (!dest->value)
		{
			free(dest->key);
			return (EXIT_FAILURE);
		}
	}
	else
		dest->value = NULL;
	return (EXIT_SUCCESS);
}
