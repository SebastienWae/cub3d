/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:00:33 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/31 11:16:50 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils/strings.h>
#include <config/parser.h>

static void	color_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	color_constructor(char *line)
{
	char	*color;
	char	**colors;
	int		rgb[3];

	color = ft_strtrim(line + 1, " \n");
	colors = ft_split(color, ',');
	free(color);
	if (array_size((void **)colors) == 3)
	{
		rgb[0] = ft_atoi(colors[0]);
		rgb[1] = ft_atoi(colors[1]);
		rgb[2] = ft_atoi(colors[2]);
		color_free_split(colors);
		if (rgb[0] < 0 || rgb[0] > 255
			|| rgb[1] < 0 || rgb[1] > 255
			|| rgb[2] < 0 || rgb[2] > 255)
			return (-1);
		return (*(int *)(unsigned char [4]){rgb[2], rgb[1], rgb[0], 2});
	}
	else
	{
		color_free_split(colors);
		return (-1);
	}
}

t_parser_state	color_handler(t_game *game, char *line, int *i)
{
	int			c_index;
	static char	*identifiers[2] = {"F ", "C "};

	c_index = *i - 4;
	if (is_empty(line))
		return (CP_S_COLORS);
	else if (c_index >= 0 && c_index <= 1)
	{
		(*i)++;
		if (ft_strncmp(identifiers[c_index], line, 2) == 0)
		{
			game->config->colors[c_index] = color_constructor(line);
			if (game->config->colors[c_index] == -1)
				return (CP_S_ERROR);
			if (c_index == 1)
				return (CP_S_MAP);
			return (CP_S_COLORS);
		}
		else
			return (CP_S_ERROR);
	}
	else
		return (CP_S_ERROR);
}
