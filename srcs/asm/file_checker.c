/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:27:39 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/12 14:05:22 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int			info_init(t_info *info, char *file)
{
	info->file = file;
	info->ins = NULL;
	info->tmp = file;
	info->line = 1;
	info->name[0] = 0;
	info->comment[0] = 0;
	info->column = 1;
	info->current_pos = 1;
	info->error = 0;
	if (!(info->labels = (t_label_list*)malloc(sizeof(t_label_list))))
		return (ft_usage(-1, info));
	info->labels->name = NULL;
	info->labels->number = 0;
	info->labels->pos = -2;
	info->labels->next = NULL;
	return (0);
}

int			ft_free_string(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (1);
}

int			check_argv(int ac, char **av, t_info *info)
{
	char	*file;
	char	buf[BUFF_SIZE + 1];
	int		fd;
	int		rd;
	int		sum;

	if (ac != 2)
		return (ft_usage(1, info));
	if (av[1][ft_strlen(av[1]) - 1] != 's'
			|| av[1][ft_strlen(av[1]) - 2] != '.')
		return (ft_usage(2, info));
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (ft_usage(3, info));
	file = ft_strnew(1);
	sum = 0;
	while ((rd = read(fd, buf, BUFF_SIZE)))
	{
		sum += rd;
		buf[rd] = '\0';
		file = ft_strjoin_left_free(file, buf);
	}
	if (!*file && ft_free_string(&file))
		return (ft_usage(3, info));
	file[sum] = '\0';
	return (info_init(info, file));
}

int			check_file_bis(t_info *info)
{
	if (!ft_strncmp(info->file, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		if (check_name(info) || skip_blanks(info))
			return (-1);
	}
	else if (!ft_strncmp(info->file, COMMENT_CMD_STRING, \
		ft_strlen(COMMENT_CMD_STRING)))
	{
		if (check_comment(info) || skip_blanks(info))
			return (-1);
	}
	else if (check_comment(info))
		return (-1);
	if ((!*info->name || !*info->comment) && free_for_all(info))
		return (ft_usage(4, info));
	return (0);
}

int			check_file(int ac, char **av, t_info *info)
{
	if (check_argv(ac, av, info) || skip_blanks(info))
		return (-1);
	if (!ft_strncmp(info->file, NAME_CMD_STRING, \
		ft_strlen(NAME_CMD_STRING)))
	{
		if (check_name(info) || skip_blanks(info))
			return (-1);
	}
	else if (!ft_strncmp(info->file, COMMENT_CMD_STRING, \
		ft_strlen(COMMENT_CMD_STRING)))
	{
		if (check_comment(info) || skip_blanks(info))
			return (-1);
	}
	return (check_file_bis(info));
}
