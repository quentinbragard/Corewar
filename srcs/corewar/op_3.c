/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzimmerm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:10:36 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/10 18:10:46 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Long load operation : Load [DIR | IND] -> [REG]
** (Unaffected by IDX_MOD).
*/

void	op_lld(t_proc *proc, t_game *game)
{
	int jump;
	int	val;
	int reg;

	if (!coding_byte(game->arena[MODM(proc->pc + 1)], \
		game->op_tab[13].params_type, 0, &jump) && !(jump = 0))
	{
		proc->jump = 2;
		val = get_param(game, proc, \
			((game->arena[MODM(proc->pc + 1)]) >> 6) & 3, 0);
		reg = game->arena[MODM(proc->pc + proc->jump)] - 1;
		if (reg >= 0 && reg <= REG_NUMBER - 1)
		{
			proc->reg[reg] = val;
			proc->carry = val ? 0 : 1;
		}
		proc->jump++;
	}
	proc->pc = MODM(proc->pc + jump + proc->jump);
}

/*
** Long load indx operation : Read @ ([REG | DIR | IND] + [REG | DIR]) -> [REG].
** (Modifies the carry unlike ldi & unaffected by IDX_MOD).
*/

void	op_lldi(t_proc *proc, t_game *game)
{
	int jump;
	int	val1;
	int val2;
	int res;
	int reg;

	if (!coding_byte(game->arena[MODM(proc->pc + 1)], \
		game->op_tab[14].params_type, 0, &jump) && !(jump = 0))
	{
		proc->jump = 2;
		val1 = get_param(game, proc, \
			((game->arena[MODM(proc->pc + 1)]) >> 6) & 3, 1);
		val2 = get_param(game, proc, \
			((game->arena[MODM(proc->pc + 1)]) >> 4) & 3, 1);
		res = get_int(game->arena, MODM(proc->pc + val1 + val2));
		reg = game->arena[MODM(proc->pc + proc->jump)] - 1;
		if (reg >= 0 && reg <= REG_NUMBER - 1)
		{
			proc->reg[reg] = res;
			proc->carry = res ? 0 : 1;
		}
		proc->jump++;
	}
	proc->pc = MODM(proc->pc + jump + proc->jump);
}

/*
** Long fork operation : Fork proc @ [DIR].
** (Unaffected by IDX_MOD).
*/

void	op_lfork(t_proc *proc, t_game *game)
{
	int	idx;

	idx = get_short(game->arena, MODM(proc->pc + 1));
	dup_proc(proc, game, MODM(proc->pc + idx));
	proc->pc = MODM(proc->pc + 3);
}

/*
** Aff operation : Print [REG] as a char on standard output.
*/

void	op_aff(t_proc *proc, t_game *game)
{
	int	jump;
	int reg;

	if (!coding_byte(game->arena[MODM(proc->pc + 1)], \
		game->op_tab[16].params_type, 0, &jump))
	{
		reg = game->arena[MODM(proc->pc + 2)] - 1;
		if (reg >= 0 && reg <= REG_NUMBER - 1)
			ft_printf("Aff: %c\n", (char)proc->reg[reg]);
	}
	proc->pc = MODM(proc->pc + jump);
}

/*
** Duplicate the proc at idx for a fork operation.
*/

void	dup_proc(t_proc *proc, t_game *game, int idx)
{
	t_proc	*new;
	int		i;

	if (!(new = (t_proc *)malloc(sizeof(t_proc))))
	{
		free_proc(game);
		exit(0);
	}
	game->player[proc->id - 1].nb_proc += 1;
	i = -1;
	while (++i < REG_NUMBER)
		new->reg[i] = proc->reg[i];
	new->pc = idx;
	new->carry = proc->carry;
	new->alive = proc->alive;
	new->cycles_to_wait = 0;
	new->op_code = 0;
	new->jump = 0;
	new->id = proc->id;
	new->next = game->proc;
	game->proc = new;
}
