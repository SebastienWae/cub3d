/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:10:46 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/11 15:08:11 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils/bool.h>

int	array_size(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	is_in_array(char **array, int lenght, char *str)
{
	int	i;

	i = 0;
	while (i < lenght)
	{
		if (ft_strncmp(array[i], str, ft_strlen(array[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
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
