/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/12 23:39:47 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** parse .s files
*/

#include "asm_parser.h"

static void				check_filename(char *filename)
{
	size_t		len;

	len = ft_strlen(filename);
	if (len < 3 || ft_strcmp(".s", filename + len - 2))
		error(E_INVALID, "Invalid file name.");
}

void					parse(char *filename)
{
	int			fd;

	check_filename(filename);
	if ((fd = open(filename, O_RDONLY)) == -1)
		error(E_OPEN, filename);
	read_header(fd, NAME_CMD_STRING);
	read_header(fd, COMMENT_CMD_STRING);
	read_loop(fd);
	if (close(fd) == -1)
		error(E_CLOSE, filename);
}
