/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 21:43:56 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/12 21:45:43 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** parse .name and .comment parts of the .s files
*/

#include "asm_parser.h"

static void				parse_header(char *line, char *cmd_string)
{
	static header_t	header = {COREWAR_EXEC_MAGIC, {0}, 0, {0}}; //TODO
	size_t			len;

	if (!ft_strcmp(cmd_string, NAME_CMD_STRING))
	{
		if ((len = ft_strlen(line)) > PROG_NAME_LENGTH)
			error(E_INVALID, "Invalid header (name too long).");
		ft_memcpy(&header.prog_name, line, len);
		ft_debugstr(NAME_CMD_STRING, header.prog_name); /* DEBUG */
	}
	else
	{
		if ((len = ft_strlen(line)) > COMMENT_LENGTH)
			error(E_INVALID, "Invalid header (comment too long).");
		ft_memcpy(&header.comment, line, len);
		ft_debugstr(COMMENT_CMD_STRING, header.comment); /* DEBUG */
	}

	//TODO: do something with header + count header.prog_size
}

static char				*check_header(char *line, char *swap) //TODO: comments
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
