/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:10:46 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/30 17:19:44 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils/bool.h>

int	array_size(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

static t_bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r')
		return (TRUE);
	return (FALSE);
}

t_bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
