/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid_rows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:56:30 by shachowd          #+#    #+#             */
/*   Updated: 2024/12/16 13:26:25 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_grid_rows(char **grid)
{
	int	len;

	len = 0;
	if (!grid)
		return (0);
	while (grid[len])
		len++;
	return (len);
}
