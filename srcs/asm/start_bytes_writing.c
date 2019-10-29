/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes_writing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 15:17:50 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/10 14:44:04 by qbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int	print_comment(t_info *info)
{
	int				i;
	int				c;
	unsigned char	quentin;

	i = -1;
	while (info->comment[++i] != '\0')
	{
		c = info->comment[i];
		write(info->fd, &c, 1);
	}
	quentin = 0;
	while (i++ < (2048 + 4))
		write(info->fd, &quentin, 1);
	return (print_instructions(info));
}

int	print_champion_size(t_info *info)
{
	unsigned int	exec_size;

	exec_size = (unsigned int)info->current_pos - 1;
	print_n_bytes(info, exec_size, 4);
	return (print_comment(info));
}

int	print_name(t_info *info)
{
	int				i;
	int				c;
	unsigned char	quentin;

	i = -1;
	while (info->name[++i] != '\0')
	{
		c = info->name[i];
		write(info->fd, &c, 1);
	}
	quentin = 0;
	while (i++ < (128 + 4))
		write(info->fd, &quentin, 1);
	return (print_champion_size(info));
}

int	print_magic_header(t_info *info)
{
	unsigned char	bytes[4];
	unsigned int	magic_header;
	int				i;

	magic_header = (unsigned int)COREWAR_EXEC_MAGIC;
	bytes[0] = (magic_header >> 24) & 0xFF;
	bytes[1] = (magic_header >> 16) & 0xFF;
	bytes[2] = (magic_header >> 8) & 0xFF;
	bytes[3] = (magic_header) & 0xFF;
	i = -1;
	while (++i < 4)
		write(info->fd, &bytes[i], 1);
	return (print_name(info));
}
