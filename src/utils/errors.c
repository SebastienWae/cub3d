/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:42:24 by seb               #+#    #+#             */
/*   Updated: 2022/06/09 17:35:55 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils/errors.h>

void	error_config(char *line)
{
	ft_putstr_fd("Error\n", 2);
	if (line)
	{
		ft_putstr_fd("Config file error at line: ", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd("\n", 2);
	}
}

static void	error_flush(char **error_buf)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(*error_buf, 2);
	free(*error_buf);
	*error_buf = NULL;
}

void	error_msg(char *msg, t_error_action action)
{
	static char	*error_buf;
	char		*tmp_buf;

	if (msg && (action == ADD || action == ADD_NO_NL))
	{
		if (action == ADD)
			msg = ft_strjoin(msg, "\n");
		else
			msg = ft_strdup(msg);
		if (error_buf)
		{
			tmp_buf = error_buf;
			error_buf = ft_strjoin(error_buf, msg);
			free(tmp_buf);
		}
		else
			error_buf = msg;
		free(msg);
	}
	else
		error_flush(&error_buf);
}
