/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bytes_writing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:01:17 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/12 14:05:00 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int	bits_to_int(char *byte, t_info *info)
{
	int i;
	int	result;

	i = -1;
	result = 0;
	while (++i < 8)
		result += ((byte[i] - 48) * (ft_pow(2, 7 - i)));
	write(info->fd, &result, 1);
	free(byte);
	return (0);
}

int	print_n_bytes(t_info *info, int value, int n)
{
	int				i;
	unsigned int	byte[n];

	i = -1;
	while (++i < n)
	{
		byte[i] = (value >> (8 * (n - (i + 1)))) & 0xFF;
		write(info->fd, &byte[i], 1);
	}
	return (0);
}

int	print_argument_type_code_2(t_info *info, t_ins *ins, char *byte)
{
	if (ins->arg_3[0] == T_REG)
		byte = ft_strjoin_left_free(byte, "01");
	else if (ins->arg_3[0] == T_IND || ins->arg_3[0] == T_IND_LAB)
		byte = ft_strjoin_left_free(byte, "11");
	else if (ins->arg_3[0] == T_DIR || ins->arg_3[0] == T_LAB)
		byte = ft_strjoin_left_free(byte, "10");
	else
		byte = ft_strjoin_left_free(byte, "00");
	byte = ft_strjoin_left_free(byte, "00");
	return (bits_to_int(byte, info));
}

int	print_argument_type_code(t_info *info, t_ins *ins)
{
	char	*byte;

	byte = ft_strnew(1);
	if (ins->arg_1[0] == T_REG)
		byte = ft_strjoin_left_free(byte, "01");
	else if (ins->arg_1[0] == T_IND || ins->arg_1[0] == T_IND_LAB)
		byte = ft_strjoin_left_free(byte, "11");
	else if (ins->arg_1[0] == T_DIR || ins->arg_1[0] == T_LAB)
		byte = ft_strjoin_left_free(byte, "10");
	if (ins->arg_2[0] == T_REG)
		byte = ft_strjoin_left_free(byte, "01");
	else if (ins->arg_2[0] == T_IND || ins->arg_2[0] == T_IND_LAB)
		byte = ft_strjoin_left_free(byte, "11");
	else if (ins->arg_2[0] == T_DIR || ins->arg_2[0] == T_LAB)
		byte = ft_strjoin_left_free(byte, "10");
	else
		byte = ft_strjoin_left_free(byte, "00");
	return (print_argument_type_code_2(info, ins, byte));
}
