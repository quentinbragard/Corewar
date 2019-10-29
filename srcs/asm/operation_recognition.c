/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_recognition.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 09:55:22 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/10 14:33:53 by qbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int		operation_recon_two(t_info *info)
{
	int ret;

	ret = 0;
	if (!ft_strncmp("ld ", info->file, 3)
			|| !ft_strncmp("ld\t", info->file, 3))
		ret = 2;
	if (!ft_strncmp("st ", info->file, 3)
			|| !ft_strncmp("st\t", info->file, 3))
		ret = 3;
	if (!ft_strncmp("or ", info->file, 3)
			|| !ft_strncmp("or\t", info->file, 3))
		ret = 7;
	if (ret)
	{
		info->file += 3;
		info->column += 3;
		return (ret);
	}
	return (ft_usage(7, info));
}

int		operation_recon_three(t_info *info)
{
	int ret;

	ret = 0;
	if (!ft_strncmp("add ", info->file, 4)
			|| !ft_strncmp("add\t", info->file, 4))
		ret = 4;
	if (!ft_strncmp("sub ", info->file, 4)
			|| !ft_strncmp("sub\t", info->file, 4))
		ret = 5;
	if (!ft_strncmp("and ", info->file, 4)
			|| !ft_strncmp("and\t", info->file, 4))
		ret = 6;
	if (!ft_strncmp("lld ", info->file, 4)
			|| !ft_strncmp("lld\t", info->file, 4))
		ret = 13;
	if (!ft_strncmp("aff ", info->file, 4)
			|| !ft_strncmp("aff\t", info->file, 4))
		ret = 16;
	if (ret)
	{
		info->file += 4;
		info->column += 4;
		return (ret);
	}
	return (operation_recon_two(info));
}

int		operation_recon_spec(t_info *info)
{
	int ret;

	ret = 0;
	if (!ft_strncmp("xor ", info->file, 4)
			|| !ft_strncmp("xor\t", info->file, 4))
		ret = 8;
	if (!ft_strncmp("sti ", info->file, 4)
			|| !ft_strncmp("sti\t", info->file, 4))
		ret = 11;
	if (!ft_strncmp("ldi ", info->file, 4)
			|| !ft_strncmp("ldi\t", info->file, 4))
		ret = 10;
	if (ret)
	{
		info->file += 4;
		info->column += 4;
		return (ret);
	}
	return (operation_recon_three(info));
}

int		operation_recon_four(t_info *info)
{
	int ret;

	ret = 0;
	if (!ft_strncmp("live ", info->file, 5)
			|| !ft_strncmp("live\t", info->file, 5))
		ret = 1;
	if (!ft_strncmp("zjmp ", info->file, 5)
			|| !ft_strncmp("zjmp\t", info->file, 5))
		ret = 9;
	if (!ft_strncmp("fork ", info->file, 5)
			|| !ft_strncmp("fork\t", info->file, 5))
		ret = 12;
	if (!ft_strncmp("lldi ", info->file, 5)
			|| !ft_strncmp("lldi\t", info->file, 5))
		ret = 14;
	if (ret)
	{
		info->file += 5;
		info->column += 5;
		return (ret);
	}
	return (operation_recon_spec(info));
}

int		operation_recon(t_info *info)
{
	int ret;

	ret = 0;
	info->column = 1;
	if (!ft_strncmp("lfork ", info->file, 6)
			|| !ft_strncmp("lfork\t", info->file, 6))
		ret = 15;
	if (ret)
	{
		info->file += 6;
		info->column += 6;
		return (ret);
	}
	return (operation_recon_four(info));
}
