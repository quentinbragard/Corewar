/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:26:35 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/12 14:05:44 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

long	ind_recon(t_info *info)
{
	int		count;
	int		neg;
	long	reg_value;

	reg_value = ft_atoi(info->file);
	count = 0;
	neg = 0;
	if (*(info->file) == '-' && (neg = 1))
	{
		info->file++;
		info->column++;
	}
	while (ft_isdigit(*(info->file)) && (++count))
	{
		info->file++;
		info->column++;
	}
	if (!count)
		return (ft_usage(6, info));
	if (count >= 19)
		reg_value = (neg == 1 ? -4294967296 : 4294967295);
	if (is_banned(*(info->file), 6, ' ', '\t', '\n', SEPARATOR_CHAR \
				, COMMENT_CHAR, ALT_COMMENT_CHAR))
		return (ft_usage(6, info));
	return (reg_value);
}

int		reg_recon(t_info *info)
{
	int	count;
	int	reg_value;

	info->file++;
	reg_value = ft_atoi(info->file);
	count = 0;
	while (ft_isdigit(*(info->file)))
	{
		count++;
		info->file++;
		info->column++;
	}
	if (!count || count > 2)
		return (-1);
	if (is_banned(*(info->file), 6, ' ', '\t', '\n', SEPARATOR_CHAR \
				, COMMENT_CHAR, ALT_COMMENT_CHAR))
		return (-1);
	return (reg_value);
}

int		label_recon(t_info *info)
{
	int		lab_len;
	int		ret;
	char	*label;

	info->file++;
	info->column++;
	lab_len = 0;
	while (info->file[lab_len] && ft_pos(info->file[lab_len], LABEL_CHARS))
		lab_len++;
	if (is_banned(info->file[lab_len], 6, ' ', '\t', '\n', SEPARATOR_CHAR
				, COMMENT_CHAR, ALT_COMMENT_CHAR))
		return (-1);
	if (!(label = ft_strndup(info->file, lab_len)))
		return (-1);
	info->column += lab_len;
	info->file += lab_len;
	ret = check_label_exist(info, label);
	free(label);
	return (ret);
}

long	direct_recon(t_info *info)
{
	long	direct_value;
	int		count;
	int		neg;

	info->file++;
	info->column++;
	direct_value = (int)ft_atoi(info->file);
	count = 0;
	neg = 0;
	if (*(info->file) == '-' && (neg = 1))
	{
		info->file++;
		info->column++;
	}
	while (ft_isdigit(*(info->file)))
	{
		count++;
		info->file++;
	}
	if (!count)
		return (ft_usage(6, info));
	if (count >= 19)
		direct_value = (neg == 1 ? -4294967296 : 4294967295);
	return (direct_value);
}

int		which_arg(t_info *info)
{
	while (is_authorized(*(info->file), 2, ' ', '\t'))
	{
		info->file++;
		info->column++;
	}
	if (*(info->file) == 'r')
		return (T_REG);
	else if (*(info->file) == DIRECT_CHAR && info->file[1]
			&& info->file[1] == LABEL_CHAR)
	{
		info->file++;
		info->column++;
		return (T_LAB);
	}
	else if (*(info->file) == DIRECT_CHAR)
		return (T_DIR);
	else if (ft_pos(*(info->file), "-0123456789"))
		return (T_IND);
	else if (*(info->file) == ':')
		return (T_IND_LAB);
	return (-1);
}
