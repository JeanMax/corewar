/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 21:43:56 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/13 01:10:30 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** parse .name and .comment parts of the .s files
*/

#include "asm_parser.h"

// <--- DEBUG
header_t	header = {COREWAR_EXEC_MAGIC, {0}, 0, {0}};

static void				debug_header()
{
	ft_debugnbr("magic", header.magic);
	ft_debugstr(NAME_CMD_STRING, header.prog_name);
	ft_debugnbr("prog_size", header.prog_size);
	ft_debugstr(COMMENT_CMD_STRING, header.comment);
	ft_putendl("");
}
// DEBUG --->

static void				parse_header(char *line, char *cmd_string)
{
	static
	size_t			len;

	if (!ft_strcmp(cmd_string, NAME_CMD_STRING))
	{
		if ((len = ft_strlen(line)) > PROG_NAME_LENGTH)
			error(E_INVALID, "Invalid header (name too long).");
		ft_memcpy(&header.prog_name, line, len);
	}
	else
	{
		if ((len = ft_strlen(line)) > COMMENT_LENGTH)
			error(E_INVALID, "Invalid header (comment too long).");
		ft_memcpy(&header.comment, line, len);

		debug_header();
	}

	//TODO: count header.prog_size
}

static char				*check_header(char *line, char *swap)
{
	while (!IS_EOL(*line) && ft_isspace(*line))
		line++;
	while (!IS_EOL(*line) && *line++ == *swap)
		swap++;
	if (*swap)
		error(E_INVALID, "Invalid header (missing identifier).");
	while (!IS_EOL(*line) && ft_isspace(*line))
		line++;
	if (*line != '"')
		error(E_INVALID, "Invalid header (missing 1st quote).");
	swap = ++line;
	while (*swap && *swap != '"')
		swap++;
	if (*swap != '"')
		error(E_INVALID, "Invalid header (missing 2nd quote).");
	*swap++ = 0;
	while (!IS_EOL(*swap))
		if (!ft_isspace(*swap++))
			error(E_INVALID, "Invalid header (weird stuffs after quotes).");
	return (line);
}

void					read_header(int fd, char *cmd_string)
{
	char		*line;
	int			ret;

	line = NULL;
	if (!(ret = get_next_line(fd, &line)) || ret == -1)
		error(E_READ, NULL);
	parse_header(check_header(line, cmd_string), cmd_string);
	ft_memdel((void **)&line);
}
