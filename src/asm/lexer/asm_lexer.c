/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 22:30:58 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/17 23:36:49 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "asm_lexer.h"


/*
** open
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** close
*/
# include <unistd.h>

static void				check_filename(char *filename)
{
	size_t		len;

	len = ft_strlen(filename);
	if (len < 3 || ft_strcmp(".s", filename + len - 2))
		error(E_INVALID, "Invalid file name.");
}

void					lex(char *filename)
{
	int			fd;

	check_filename(filename);
	if ((fd = open(filename, O_RDONLY)) == -1)
		error(E_OPEN, filename);
	read_header(fd);
	read_loop(fd);
	if (close(fd) == -1)
		error(E_CLOSE, filename);
}
