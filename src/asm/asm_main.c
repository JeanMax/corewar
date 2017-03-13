/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 00:12:49 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/11 18:15:50 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this is the main...
*/

#include "asm.h"

char			*g_exec_name;

int				main(int ac, char **av)
{
	g_exec_name = *av++;

	if (ac != 2)
		error(E_USAGE_ASM, NULL);

	if (!ft_strcmp("-h", *av))
		error(E_USAGE_ASM | E_NOEXIT, NULL);
	else
		parse(*av);

	return (EXIT_SUCCESS);
}
