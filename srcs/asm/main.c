/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:09:47 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/12 13:59:50 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_ins	*ins_malloc_initialization(t_info *info)
{
	t_ins	*ins;
	int		i;

	if (!(ins = (t_ins *)malloc(sizeof(t_ins))))
		return (NULL);
	ins->op_code = 0;
	if (!(ins->arg_1 = (long long *)malloc(sizeof(long long) * 2)))
		return (NULL);
	if (!(ins->arg_2 = (long long *)malloc(sizeof(long long) * 2)))
		return (NULL);
	if (!(ins->arg_3 = (long long *)malloc(sizeof(long long) * 2)))
		return (NULL);
	i = -1;
	while (++i < 2)
	{
		ins->arg_1[i] = 0;
		ins->arg_2[i] = 0;
		ins->arg_3[i] = 0;
	}
	ins->pos = info->current_pos;
	ins->instruc_size = 0;
	ins->next = NULL;
	return (ins);
}

int		create_file(t_info *info, char *name)
{
	char	*to_print;
	char	*to_join;

	to_join = ft_strsub(name, 0, ft_strlen(name) - 2);
	to_print = ft_strjoin(to_join, ".cor");
	if ((info->fd = open(to_print, O_CREAT | O_WRONLY | O_APPEND
					| O_TRUNC, 0600)) == -1)
		return (-1);
	free(to_print);
	free(to_join);
	return (0);
}

int		print_result(char *name)
{
	char	*to_print;
	char	*to_join;

	to_join = ft_strsub(name, 0, ft_strlen(name) - 2);
	to_print = ft_strjoin(to_join, ".cor");
	ft_printf("Writing output program to %s\n", to_print);
	free(to_print);
	free(to_join);
	return (0);
}

int		main(int ac, char **av)
{
	t_info	info;
	int		i;

	i = 0;
	if (check_file(ac, av, &info))
		return (-1);
	if (!(info.ins = ins_malloc_initialization(&info)))
		return (ft_usage(-1, &info));
	if ((i = instructions_init(&info, info.ins)) == 1)
	{
		*info.file = 1;
		ft_usage(6, &info);
		return (free_for_all(&info));
	}
	while (!(i = get_instruction_list(&info, info.ins)))
		if (info.error)
			return (free_for_all(&info));
	if (info.error)
		return (free_for_all(&info));
	create_file(&info, av[1]);
	if (update_labels(&info) == -1 && (*info.file = 1) && ft_usage(12, &info))
		return (free_for_all(&info));
	print_magic_header(&info);
	free_for_all(&info);
	return (print_result(av[1]));
}
