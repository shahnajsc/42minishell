/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:50:29 by shachowd          #+#    #+#             */
/*   Updated: 2025/02/02 15:59:03 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_grid_dup(char **grid)
{
	int		rows;
	int		count;
	char	**dup_grid;

	count = 0;
	rows = ft_grid_rows(grid);
	dup_grid = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!dup_grid)
		return (NULL);
	while (count < rows)
	{
		dup_grid[count] = ft_strdup(grid[count]);
		if (!dup_grid[count])
		{
			ft_free_grid((void **)grid);
			return (NULL);
		}
		count++;
	}
	dup_grid[count] = NULL;
	return (dup_grid);
}
