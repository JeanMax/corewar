/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 21:43:56 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/18 00:36:05 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** read .name and .comment parts of the .s files
*/

#include "asm_lexer.h"

// <--- DEBUG
header_t	header = {COREWAR_EXEC_MAGIC, {0}, 0, {0}};

static void				debug_header()
{
	ft_debugnbr("magic", (int)header.magic);
	ft_debugstr(NAME_CMD_STRING, header.prog_name);
	ft_debugnbr("prog_size", (int)header.prog_size);
	ft_debugstr(COMMENT_CMD_STRING, header.comment);
	ft_putendl("");
}
// DEBUG --->

static enum e_progress	parse_header(char *line, enum e_progress progress)
{
	static
	size_t			len;

	if (progress & P_NAME)
	{
		if ((len = ft_strlen(line)) > PROG_NAME_LENGTH)
			error(E_INVALID, "Invalid header (name too long).");
		ft_memcpy(&header.prog_name, line, len);
	}
	else if (progress & P_COMMENT)
	{
		if ((len = ft_strlen(line)) > COMMENT_LENGTH)
			error(E_INVALID, "Invalid header (comment too long).");
		ft_memcpy(&header.comment, line, len);
	}

	return (progress);
	//TODO: count header.prog_size
}

static void				read_quoted_string(char *line)
{
	if (*line != '"')
		error(E_INVALID, "Invalid header (missing 1st quote).");
	++line;
	while (*line && *line != '"')
		line++;
	if (*line != '"')
		error(E_INVALID, "Invalid header (missing 2nd quote).");
	*line++ = 0;
	while (!IS_EOL(*line))
		if (!ft_isspace(*line++))
			error(E_INVALID, "Invalid header (weird stuffs after quotes).");
}

static enum e_progress	read_identifier(char *line)
{
	if (!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (P_NAME);
	if (!ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return (P_COMMENT);

	error(E_INVALID, "Invalid header (unknown identifier)."); //TODO: it could be a 'missing header' error
	return (P_NOPROGRESS);
}

static enum e_progress	check_header(char *line)
{
	enum e_progress	progress;

	while (!IS_EOL(*line) && ft_isspace(*line))
		line++;
	if (IS_EOL(*line))
		return (P_NOPROGRESS);

	progress = read_identifier(line);

	while (!IS_EOL(*line) && !ft_isspace(*line))
		line++;
	while (!IS_EOL(*line) && ft_isspace(*line))
		line++;

	read_quoted_string(line);

	return (parse_header(line + 1, progress));
}

void					read_header(int fd)
{
	int				ret;
	char			*line;
	enum e_progress	progress;

	progress = P_NOPROGRESS;
	while (!(progress & P_NAME && progress & P_COMMENT))
	{
		line = NULL;
		if (!(ret = get_next_line(fd, &line)) || ret == -1)
			error(E_READ, NULL);

		progress |= check_header(line);

		ft_memdel((void **)&line);
	}

	debug_header();
}
