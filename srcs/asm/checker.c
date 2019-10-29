/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzimmerm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:00:04 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/12 14:00:35 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int	check_name_bis(t_info *info, int start, int end)
{
	int i;

	i = -1;
	while (++i < end - start - 1)
	{
		info->name[i] = info->file[start + i + 1];
		if (*info->file == '\n')
		{
			info->line++;
			info->column++;
		}
		else
			info->column++;
	}
	info->name[i] = '\0';
	info->file += end + 1;
	while (*info->file != '\n')
	{
		if (!is_authorized(*info->file, 2, ' ', '\t') && free_for_all(info))
			return (ft_usage(4, info));
		info->file++;
	}
	info->file++;
	info->line++;
	return (0);
}

int			check_name(t_info *info)
{
	int	start;
	int	end;

	if (skip_blanks(info) < 0)
		return (-1);
	start = ft_strlen(NAME_CMD_STRING);
	if (ft_strncmp(info->file, NAME_CMD_STRING, start) && free_for_all(info))
		return (ft_usage(4, info));
	while (info->file[start] == ' ' || info->file[start] == '\t')
		start++;
	if (info->file[start] && info->file[start] != '"' && free_for_all(info))
		return (ft_usage(4, info));
	end = start + 1;
	while (info->file[end] && info->file[end] != '"')
		end++;
	if (!info->file[end] && free_for_all(info))
		return (ft_usage(5, info));
	if ((end - start - 1 > PROG_NAME_LENGTH || end == start + 1) \
		&& free_for_all(info))
		return (ft_usage(4, info));
	return (check_name_bis(info, start, end));
}

static int	check_comment_2(t_info *info, int start, int end)
{
	int i;

	i = -1;
	while (++i < end - start - 1)
	{
		info->comment[i] = info->file[start + i + 1];
		if (*info->file == '\n')
		{
			info->line++;
			info->column++;
		}
		else
			info->column++;
	}
	info->comment[i] = '\0';
	info->file += end + 1;
	while (*info->file != '\n')
	{
		if (!is_authorized(*info->file, 2, ' ', '\t') && free_for_all(info))
			return (ft_usage(5, info));
		info->file++;
	}
	info->file++;
	info->line++;
	return (0);
}

int			check_comment(t_info *info)
{
	int	start;
	int	end;

	if (skip_blanks(info) < 0)
		return (-1);
	start = ft_strlen(COMMENT_CMD_STRING);
	if (ft_strncmp(info->file, COMMENT_CMD_STRING, start) && free_for_all(info))
		return (ft_usage(5, info));
	while (info->file[start] == ' ' || info->file[start] == '\t')
		start++;
	if (info->file[start] && info->file[start] != '"' && free_for_all(info))
		return (ft_usage(5, info));
	end = start + 1;
	while (info->file[end] && info->file[end] != '"')
		end++;
	if (!info->file[end] && free_for_all(info))
		return (ft_usage(5, info));
	if ((end - start - 1 > COMMENT_LENGTH || end == start + 1) \
		&& free_for_all(info))
		return (ft_usage(5, info));
	return (check_comment_2(info, start, end));
}
