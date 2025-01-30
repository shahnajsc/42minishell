/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:18:48 by shachowd          #+#    #+#             */
/*   Updated: 2024/09/27 11:44:12 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	count;

	count = 0;
	if (n == 0)
	{
		return (0);
	}
	while ((s1[count] == s2[count]) && s1[count] && (count < n - 1))
	{
		count++;
	}
	if (s1[count] == s2[count])
	{
		return (0);
	}
	else
	{
		return ((unsigned char)(s1[count]) - (unsigned char)(s2[count]));
	}
}
/*
 - The strcmp() and strncmp() functions lexicographically compare
 	the null terminated strings s1 and s2.
 - The strncmp() function compares not more than n characters
 - strncmp() is designed for comparing strings rather
 	than binary data
 - characters that appear after a `\0' character are not compared
*/
