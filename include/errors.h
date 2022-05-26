/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:25:02 by seb               #+#    #+#             */
/*   Updated: 2022/05/26 22:47:25 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum e_err_type
{
	ERR_TOO_MANY_ARGS,
	ERR_MISSING_ARGS
}	t_err_type;

void	error_exit(t_err_type err_type);

#endif
