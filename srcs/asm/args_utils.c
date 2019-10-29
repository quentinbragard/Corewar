/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 15:19:02 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/10 14:09:16 by qbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int	ft_aff(t_info *info, t_ins *ins)
{
	if ((ins->arg_1[0] = possible_args(info, 1, T_REG)) < 0)
		return (ft_usage(9, info));
	if ((ins->arg_1[1] = get_arg(info, ins->arg_1[0])) < 0)
		return (ft_usage(10, info));
	return (0);
}

int	next_arg(t_info *info)
{
	while (is_authorized(*(info->file), 2, ' ', '\t'))
	{
		info->file++;
		info->column++;
	}
	if (*(info->file) != SEPARATOR_CHAR)
		return (-1);
	info->file++;
	info->column++;
	return (0);
}

int	possible_args(t_info *info, int n, ...)
{
	int		i;
	int		arg[n];
	int		to_compare;
	va_list	ap;

	i = -1;
	va_start(ap, n);
	while (++i < n)
		arg[i] = va_arg(ap, int);
	to_compare = which_arg(info);
	i = -1;
	while (++i < n)
		if (arg[i] == to_compare)
			return (arg[i]);
	va_end(ap);
	return (-1);
}

int	get_arg(t_info *info, int arg)
{
	if (arg == T_REG)
		return (reg_recon(info));
	else if (arg == T_DIR)
		return (direct_recon(info));
	else if (arg == T_LAB)
	{
		return (label_recon(info));
	}
	else if (arg == T_IND)
		return (ind_recon(info));
	else if (arg == T_IND_LAB)
		return (label_recon(info));
	return (-1);
}
