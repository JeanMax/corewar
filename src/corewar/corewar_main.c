/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 00:12:49 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/19 20:05:17 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this is the main...
*/

#include "corewar.h"

char			*g_exec_name = NULL;
int				g_fd = -1;

int				main(int ac, char **av)
{
	g_exec_name = *av;

	if (ac != 1)
		error(E_USAGE_COREWAR, NULL);

	return (EXIT_SUCCESS);
}
