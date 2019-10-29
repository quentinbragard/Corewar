/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:09:24 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/12 14:01:10 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void	ft_usage_helper(int error, t_info *info)
{
	if (error == 7)
		ft_printf("Operation doesn't exist (line %d : column 1).", info->line);
	if (error == 8)
		ft_printf("Wrong number of arguments (line %d).", info->line);
	if (error == 9)
		ft_printf("Wrong type of argument (line %d : column %d).",
				info->line, info->column);
	if (error == 10)
		ft_printf("Register value incorrect (line %d : column %d).",
				info->line, info->column);
	if (error == 11)
		ft_printf("Last instruction must finish with a new line");
	if (error == 12)
		ft_printf("Incorrect label call.");
	if (error == -1)
		ft_printf("Memory issue.");
}

int			ft_usage(int error, t_info *info)
{
	if (info->tmp && (*(info->file) == '\0' || info->error == 1))
		return (-1);
	info->error = 1;
	write(1, "Error : ", 8);
	if (error == 1)
		ft_printf("Wrong number of arguments.");
	if (error == 2)
		ft_printf("Wrong extension file.");
	if (error == 3)
		ft_printf("File couldn't be read.");
	if (error == 4)
		ft_printf("Invalid or empty name (line %d).", info->line);
	if (error == 5)
		ft_printf("Invalid or empty comment (line %d).", info->line);
	if (error == 6)
		ft_printf("Syntax error (line %d : column %d).", info->line, \
			info->column);
	ft_usage_helper(error, info);
	ft_printf(" Use --help for usage (PF)\n");
	return (-1);
}
