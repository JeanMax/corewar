/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/11 18:04:54 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H

# define UTIL_H

# include "libft.h"

/*
** error code enum
*/
enum					e_error
{
	E_NOERROR = 0,
	E_NOEXIT = (1 << 0),
	E_USAGE_COREWAR = (1 << 1),
	E_USAGE_ASM = (1 << 2),
	E_READ = (1 << 3),
	E_OPEN = (1 << 4),
	E_CLOSE = (1 << 5),
	E_INVALID = (1 << 6)
};

/*
** globad
*/
extern char				*g_exec_name;

/*
** error.c
*/
void					error(t_uint flag, char *msg);

#endif