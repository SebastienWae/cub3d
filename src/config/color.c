/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:00:33 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/11 16:26:38 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <config/parser.h>
#include <utils/strings.h>
#include <utils/bool.h>

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

t_bool	color_handler(char *line, t_game *game)
{
	int			id;
	static char	*c_ids[2] = {"F ", "C "};

	id = is_in_array(c_ids, 2, line);
	if (id >= 0)
	{
		if (game->config->colors[id])
			return (FALSE);
		game->config->colors[id] = color_constructor(line);
		if (!game->config->colors[id])
			return (FALSE);
		if (game->config->colors[id] == -1)
			return (FALSE);
		return (TRUE);
	}
	else
		return (FALSE);
}
