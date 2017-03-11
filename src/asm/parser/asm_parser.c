/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/11 23:39:53 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** parse .s files
*/

#include "asm_parser.h"

static void		parse_code(char *line)
{
	ft_debugstr("code", line); /* DEBUG */
}

static void		read_loop(int fd)
{
	int			ret;
	char		*line;

	line = NULL;
	if (!(ret = get_next_line(fd, &line)))
		return ;
	else if (ret == -1)
		error(E_READ, NULL);

	if (*line)
		parse_code(line);

	ft_memdel((void **)&line);
	read_loop(fd);
}

static void		parse_header(char *line, char *type)
{
	static header_t	header = {COREWAR_EXEC_MAGIC, {0}, 0, {0}}; //TODO
	size_t			len;

	if (*type == 'n')
	{
		if ((len = ft_strlen(line)) > PROG_NAME_LENGTH)
			error(E_INVALID, "Invalid header (name too long).");
		ft_memcpy(&header.prog_name, line, len);
		ft_debugstr("prog_name", header.prog_name); /* DEBUG */
	}
	else
	{
		if ((len = ft_strlen(line)) > COMMENT_LENGTH)
			error(E_INVALID, "Invalid header (comment too long).");
		ft_memcpy(&header.comment, line, len);
		ft_debugstr("comment", header.comment); /* DEBUG */
	}

	//TODO: do something with header
}

static char		*check_header(char *line, char *swap)
{
	while (*line++ == *swap)
		swap++;
	if (*swap)
		error(E_INVALID, "Invalid header (missing identifier).");
	while (*line && ft_isspace(*line))
		line++;
	if (*line != '"')
		error(E_INVALID, "Invalid header (missing 1st quote).");
	swap = ++line;
	while (*swap && *swap != '"')
		swap++;
	if (*swap != '"')
		error(E_INVALID, "Invalid header (missing 2nd quote).");
	*swap++ = 0;
	while (*swap)
		if (!ft_isspace(*swap++))
			error(E_INVALID, "Invalid header (weird stuffs after quotes).");
	return (line);
}

static void		read_header(int fd, char *type)
{
	char		*line;
	int			ret;

	line = NULL;
	if (!(ret = get_next_line(fd, &line)) || ret == -1)
		error(E_READ, NULL);
	parse_header(check_header(line, type), type + 1);
	ft_memdel((void **)&line);
}

static void		check_filename(char *filename)
{
	size_t		len;

	len = ft_strlen(filename);
	if (len < 3 || ft_strcmp(".s", filename + len - 2))
		error(E_INVALID, "Invalid file name.");
}

void			parse(char *filename)
{
	int			fd;

	check_filename(filename);
	if ((fd = open(filename, O_RDONLY)) == -1)
		error(E_OPEN, filename);
	read_header(fd, ".name");
	read_header(fd, ".comment");
	read_loop(fd);
	if (close(fd) == -1)
		error(E_CLOSE, filename);
}
